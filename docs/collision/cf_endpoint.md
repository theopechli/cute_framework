[//]: # (This file is automatically generated by Cute Framework's docs parser.)
[//]: # (Do not edit this file by hand!)
[//]: # (See: https://github.com/RandyGaul/cute_framework/blob/master/samples/docs_parser.cpp)
[](../header.md ':include')

# cf_endpoint

Category: [collision](/api_reference?id=collision)  
GitHub: [cute_math.h](https://github.com/RandyGaul/cute_framework/blob/master/include/cute_math.h)  
---

Returns the endpoint of a ray.

```cpp
CF_V2 cf_endpoint(CF_Ray r)
```

## Remarks

Rays are defined to have an endpoint as an optimization. Usually infinite rays are not needed in games, and cause
unnecessarily large computations when doing raycasts.

## Related Pages

[CF_Ray](/math/cf_ray.md)  
[cf_impact](/collision/cf_impact.md)  
