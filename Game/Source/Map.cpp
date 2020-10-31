
#include "App.h"
#include "Render.h"
#include "Textures.h"
#include "Map.h"

#include "Defs.h"
#include "Log.h"

#include <math.h>

Map::Map() : Module(), mapLoaded(false)
{
    name.Create("map");
}

// Destructor
Map::~Map()
{}

// Called before render is available
bool Map::Awake(pugi::xml_node& config)
{
    LOG("Loading Map Parser");
    bool ret = true;

    folder.Create(config.child("folder").child_value());

    return ret;
}

// Draw the map (all requried layers)
void Map::Draw()
{
	if (mapLoaded == false) return;

	// L04: TODO 5: Prepare the loop to draw all tilesets + DrawTexture()
	// L04: TODO 9: Complete the draw function
	// L06: TODO 4: Make sure we draw all the layers and not just the first one

	ListItem<MapLayer*>*L;
	L = data.mapLayers.start;

	TileSet* tileset = NULL;
	while (L != NULL) // Iterate all layers
	{
		if (L->data->properties.GetProperty("Drawable", 1) == 0) // Drawable property is false
		{
			L = L->next;
			continue;
		}
		
		for (int j = 0; j < L->data->height; ++j) // Start at first row
		{
			for (int i = 0; i < L->data->width; ++i) // Iterate all collumns
			{
				int tileId = L->data->Get(i, j);
				if (tileId > 0)
				{
					tileset = GetTilesetFromTileId(tileId);

					SDL_Rect r = tileset->GetTileRect(tileId);
					iPoint pos = MapToWorld(i, j);

					app->render->DrawTexture(tileset->texture, pos.x, pos.y, &r);
				}
			}
		}

		L = L->next;
	}
}

// L04: DONE 8: Create a method that translates x,y coordinates from map positions to world positions
iPoint Map::MapToWorld(int x, int y) const
{
	iPoint ret;
	if (MapTypes::MAPTYPE_ORTHOGONAL)
	{
		ret.x = x * data.tileWidth;
		ret.y = y * data.tileHeight;
	}
	// L05: DONE 1: Add isometric map to world coordinates
	else if (MapTypes::MAPTYPE_ISOMETRIC)
	{
		ret.x = x * (app->map->data.tileWidth / 2) - y * (app->map->data.tileWidth / 2);
		ret.y = x * (app->map->data.tileHeight / 2) - y * (app->map->data.tileHeight / 2);
	}
	else
	{
		LOG("Unknown map type");
		ret.x = x;
		ret.y = y;
	}

	return ret;
}

// L05: TODO 2: Add ortographic world to maap coordinates
iPoint Map::WorldToMap(int x, int y) const
{
	iPoint ret(0, 0);
	if (data.type == MAPTYPE_ORTHOGONAL)
	{
		ret.x = x / data.tileWidth;
		ret.y = y / data.tileHeight;
	}
	// L05: DONE 3: Add the case for isometric maps to WorldMap
	else if (data.type == MAPTYPE_ISOMETRIC)
	{
		float halfWidth = data.tileWidth * 0.5f;
		float halfHeight = data.tileHeight * 0.5f;
		ret.x = int((x / halfWidth + y / halfHeight) / 2);
		ret.y = int((y /halfHeight - x / halfWidth) / 2);
	}
	else
	{
		LOG("Unknown map type");
		ret.x = x;
		ret.y = y;
	}

	return ret;
}


// Called before quitting
bool Map::CleanUp()
{
    LOG("Unloading map");

    // L03: DONE 2: Make sure you clean up any memory allocated from tilesets/map
    // Remove all tilesets
	ListItem<TileSet*>* tilesetsList;
	tilesetsList = data.tilesets.start;

	while (tilesetsList != NULL)
	{
		RELEASE(tilesetsList->data);
		tilesetsList = tilesetsList->next;
	}
	data.tilesets.clear();

	// L04: TODO 2: clean up all layer data
	// Remove all layers
	ListItem<MapLayer*>* layerList;
	layerList = data.mapLayers.start;

	while (layerList != NULL)
	{
		RELEASE(layerList->data);
		layerList = layerList->next;
	}
	data.mapLayers.clear();

	// Clean up the pugui tree
	mapFile.reset();

    return true;
}

// Load new map
bool Map::Load(const char* filename)
{
    bool ret = true;
    SString tmp("%s%s", folder.GetString(), filename);

    pugi::xml_parse_result result = mapFile.load_file(tmp.GetString());

    if(result == NULL)
    {
        LOG("Could not load map xml file %s. pugi error: %s", filename, result.description());
        ret = false;
    }

    if(ret == true)
    {
        // L03: DONE 3: Create and call a private function to load and fill all your map data
		ret = LoadMap();
	}

    // L03: DONE 4: Create and call a private function to load a tileset
    // remember to support more any number of tilesets!
	pugi::xml_node tilesetNode;
	for (tilesetNode = mapFile.child("map").child("tileset"); tilesetNode && ret; tilesetNode = tilesetNode.next_sibling("tileset"))
	{
		TileSet* tilesetLayerSet = new TileSet(); // Create new tileset

		if (ret == true) ret = LoadTilesetDetails(tilesetNode, tilesetLayerSet);

		if (ret == true) ret = LoadTilesetImage(tilesetNode, tilesetLayerSet);

		data.tilesets.add(tilesetLayerSet); // Add the filled tileset to the list of tilesets
	}

	// L04: DONE 4: Iterate all layers and load each of them
	// Load layer info
	pugi::xml_node layerNode;
	for (layerNode = mapFile.child("map").child("layer"); layerNode && ret; layerNode = layerNode.next_sibling("layer"))
	{
		MapLayer* mapLayerSet = new MapLayer(); // Create new map layer

		ret = LoadLayer(layerNode, mapLayerSet);

		if (ret == true) data.mapLayers.add(mapLayerSet); // Add the filled map layer to the list of map layers
	}


    if(ret == true)
    {
		// L03: TODO 5: LOG all the data loaded iterate all tilesets and LOG everything
		// L04: TODO 4: LOG the info for each loaded layer
		LogInfo();
    }

    mapLoaded = ret;

    return ret;
}

// L03: TODO: Load map general properties
bool Map::LoadMap()
{
	bool ret = true;
	pugi::xml_node mapNode = mapFile.child("map");

	if (mapNode == NULL)
	{
		LOG("Error parsing map xml file: Cannot find 'map' tag.");
		ret = false;
	}
	else
	{
		// L03: TODO: Load map general properties
		LOG("Filling Map info");
		//data.renderorder = map.attribute("renderorder").as_string();
		data.width = mapNode.attribute("width").as_int();
		data.height = mapNode.attribute("height").as_int();
		data.tileWidth = mapNode.attribute("tilewidth").as_int();
		data.tileHeight = mapNode.attribute("tileheight").as_int();
		data.nextObjectId = mapNode.attribute("nextobjectid").as_int();
		
		SString strType(mapNode.attribute("orientation").as_string());
		if (strType == "orthogonal")
		{
			data.type = MAPTYPE_ORTHOGONAL;
		}
		else if (strType == "isometric")
		{
			data.type = MAPTYPE_ISOMETRIC;
		}
		else if (strType == "staggered")
		{
			data.type = MAPTYPE_STAGGERED;
		}
		else 
		{
			data.type = MAPTYPE_UNKNOWN;
		}
	}

	return ret;
}

// L03: TODO: Load Tileset attributes
bool Map::LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set)
{
	bool ret = true;
	
	// L03: TODO: Load Tileset attributes
	LOG("Filling TilesetDetails");
	set->firstgid = tileset_node.attribute("firstgid").as_int();
	set->name = tileset_node.attribute("name").as_string();
	set->tileWidth = tileset_node.attribute("tilewidth").as_int();
	set->tileHeight = tileset_node.attribute("tileheight").as_int();
	set->spacing = tileset_node.attribute("spacing").as_int();
	set->margin = tileset_node.attribute("margin").as_int();

	return ret;
}

// L03: TODO: Load Tileset image
bool Map::LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set)
{
	bool ret = true;
	pugi::xml_node image = tileset_node.child("image");

	if (image == NULL)
	{
		LOG("Error parsing tileset xml file: Cannot find 'image' tag.");
		ret = false;
	}
	else
	{
		// L03: TODO: Load Tileset image
		LOG("Filling TilesetDetails");
		SString tmp("%s%s", folder.GetString(), image.attribute("source").as_string());
		set->texture = app->tex->Load(tmp.GetString());
		set->texWidth = image.attribute("width").as_int();
		set->texHeight = image.attribute("height").as_int();

		set->numTilesWidth = set->texWidth / set->tileWidth;
		set->numTilesHeight = set->texHeight / set->tileHeight;
		set->offsetX = 0;
		set->offsetY = 0;
	}
	return ret;
}

// L04: TODO 3: Create the definition for a function that loads a single layer
bool Map::LoadLayer(pugi::xml_node& node, MapLayer* layer)
{
	bool ret = true;
	// Node points to layer

	// L04: TODO 3: Load a single layer
	layer->name = node.attribute("name").as_string();
	layer->width = node.attribute("width").as_int();
	layer->height = node.attribute("height").as_int();
	layer->data = new uint[(data.width * data.height * sizeof(uint))];
	memset(layer->data, 0, size_t(data.width * data.height * sizeof(uint)));
	
	pugi::xml_node gidNode;
	int i = 0;
	for (gidNode = node.child("data").child("tile"); gidNode && ret; gidNode = gidNode.next_sibling("tile"))
	{
		if (ret == true) layer->data[i] = gidNode.attribute("gid").as_uint();
		++i;
	}

	LoadProperties(node, layer->properties);

	LOG("Layer <<%s>> has loaded %d tiles", layer->name.GetString(), i);
	return ret;
}

// L06: TODO 6: Load a group of properties from a node and fill a list with it
bool Map::LoadProperties(pugi::xml_node& node, Properties& properties)
{
	bool ret = true;
	pugi::xml_node propertyNode = node.child("properties").child("property");
	while (propertyNode != NULL && ret)
	{
		Properties::Property* prop = new Properties::Property();

		prop->name = propertyNode.attribute("name").as_string("Not found");
		prop->type = propertyNode.attribute("type").as_string("Not found");
		prop->value = propertyNode.attribute("value").as_int(0);

		properties.propertyList.add(prop);

		propertyNode = propertyNode.next_sibling("property");
	}
	return ret;
}

int Map::LoadCollisions()
{
	int count = 0;

	ListItem<MapLayer*>* listLayers;
	listLayers = data.mapLayers.start;
	SString colliderTilesetName("colliders");
	while (listLayers != NULL)
	{
		SString name = listLayers->data->name;
		if (name == colliderTilesetName)
		{
			break;
		}
		listLayers = listLayers->next;
	}

	TileSet* tileset = NULL;
	for (int j = 0; j < data.height; ++j)
	{
		for (int i = 0; i < data.width; ++i)
		{
			int tileId = listLayers->data->Get(i, j);
			if (tileId > 0)
			{
				iPoint pos = MapToWorld(i, j);
				SDL_Rect r =
				{
					pos.x,
					pos.y,
					data.tileWidth,
					data.tileHeight
				};
				tileset = GetTilesetFromTileId(tileId);
				int relativeId = tileset->GetRelativeId(tileId);

				switch (relativeId)
				{
				case 0: // Void --> Do nothing
				case 1: // Red color --> Lava
					// AddCollider(r, Collider::Type::LAVA)
				case 2: // Blue color --> Block
					// AddCollider(r, Collider::Type::BLOCK)
				}
					
			}
		}
	}
	// count = getcolliderscount
	return count;
}

// L06: TODO 7: Ask for the value of a custom property
int Properties::GetProperty(const char* nameProperty, int defaultValue) const
{
	//...
	ListItem<Property*>* item = propertyList.start;
	while (item != NULL)
	{
		if (item->data->name == nameProperty)
			return item->data->value;
		item = item->next;
	}
	return defaultValue;
}

// L06: TODO 3: Pick the right Tileset based on a tile id
TileSet* Map::GetTilesetFromTileId(int id) const
{
	ListItem<TileSet*>* tilesetsList = data.tilesets.start;
	TileSet* tileset = tilesetsList->data;
	while (tilesetsList != NULL)
	{
		if (id < tilesetsList->data->firstgid)
		{
			tileset = tilesetsList->prev->data;
			break;
		}
		tileset = tilesetsList->data;
		tilesetsList = tilesetsList->next;
	}
	return tileset;
}

// Get relative Tile rectangle
SDL_Rect TileSet::GetTileRect(int id) const
{
	SDL_Rect rect = { 0 };

	// L04: DONE 7: Get relative Tile rectangle
	int relativeId = id - firstgid;
	rect.w = tileWidth;
	rect.h = tileHeight;
	rect.x = margin + ((rect.w + spacing) * (relativeId % numTilesWidth));
	rect.y = margin + ((rect.h + spacing) * (relativeId / numTilesWidth));

	return rect;
}

int TileSet::GetRelativeId(int tileId)const
{
	int relativeId = tileId - firstgid;
	return relativeId;
}

bool Map::StringToBool(const char* string)
{
	bool result = false;
	if (string == "true") result = true;
	else if (string == "false") result = false;
	return result;
}

void Map::LogInfo()
{
	// L03: TODO 5: LOG all the data loaded iterate all tilesets and LOG everything
	LOG("--------------------------------------------------------------------------");
	LOG("<< MAP DATA >>");
	LOG("Width=%d", data.width);
	LOG("Height=%d", data.height);
	LOG("TileWidth=%d", data.tileWidth);
	LOG("TileHeight=%d", data.tileHeight);
	LOG("<< END DATA >>\n");

	ListItem<TileSet*>* tilesetsList;
	tilesetsList = data.tilesets.start;
	int i = 1;
	while (tilesetsList != NULL)
	{
		LOG("<< TILESET %d>>", i);
		LOG("Name=%s", tilesetsList->data->name.GetString());
		LOG("Firstgid=%d", tilesetsList->data->firstgid);
		LOG("Margin=%d", tilesetsList->data->margin);
		LOG("Spacing=%d", tilesetsList->data->spacing);
		LOG("Tile_width=%d", tilesetsList->data->tileWidth);
		LOG("Tile_height=%d", tilesetsList->data->tileHeight);

		LOG("texWidth=%d", tilesetsList->data->texWidth);
		LOG("texHeight=%d", tilesetsList->data->texHeight);
		LOG("numTilesWidth=%d", tilesetsList->data->numTilesWidth);
		LOG("numTilesHeight=%d", tilesetsList->data->numTilesHeight);
		LOG("<< END TILESET >>\n");

		tilesetsList = tilesetsList->next;
		++i;
	}
	
	// L04: TODO 4: LOG the info for each loaded layer
	ListItem<MapLayer*>* mapLayersList;
	mapLayersList = data.mapLayers.start;
	i = 1;
	while (mapLayersList != NULL)
	{
		LOG("<< LAYER %d>>", i);
		LOG("Name=%s", mapLayersList->data->name.GetString());
		LOG("Width=%d", mapLayersList->data->width);
		LOG("Height=%d", mapLayersList->data->height);
		LOG("<< END LAYER >>\n");
		mapLayersList = mapLayersList->next;
		++i;
	}
	LOG("--------------------------------------------------------------------------");
}