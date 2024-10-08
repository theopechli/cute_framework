[//]: # (This file is automatically generated by Cute Framework's docs parser.)
[//]: # (Do not edit this file by hand!)
[//]: # (See: https://github.com/RandyGaul/cute_framework/blob/master/samples/docs_parser.cpp)
[](../header.md ':include')

# CF_AtlasSubImage

Category: [draw](/api_reference?id=draw)  
GitHub: [cute_draw.h](https://github.com/RandyGaul/cute_framework/blob/master/include/cute_draw.h)  
---

Represents a single sub-image within an atlas, defined by a uv coordinate pair.

Struct Members | Description
--- | ---
`uint64_t image_id` | Must be a unique number for all sub-images across all atlases. You should start at 0 and increment for each unique id you need.
`int w, h` | The width in height, in pixels, of the sub-image.
`float minx, miny` | u coordinate in the premade atlas.
`float maxx, maxy` | v coordinate in the premade atlas.

## Related Pages

[cf_make_premade_sprite](/draw/cf_make_premade_sprite.md)  
[cf_register_premade_atlas](/draw/cf_register_premade_atlas.md)  
