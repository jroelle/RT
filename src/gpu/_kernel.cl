__kernel void processed(
    __global t_vec3 *output,
    int width,
    int height,
    int oc, /* objects count */
    __global t_object *objects,
    int mc, /* models count */
    __global t_model *models,
    __global unsigned int *seed,
    int depth,
    t_camera camera,
    __global t_vec3 *assets)
{
    int id = get_global_id(0);
    if (id < 0 || id >= width * height)
        return ;

    t_trace trace;
    t_vec3 color;
    
    trace.seeds;
    trace.seeds.x = seed[id];
    trace.seeds.y = seed[id + width * height];

    int iy = id / width;
    int ix = id % width;

    double x = ix + (double)get_random(&trace.seeds) - 0.5;
    double y = iy + (double)get_random(&trace.seeds) - 0.5;

    trace.id = id;
    trace.x = x;
    trace.y = y;
 
    trace.ray.position = camera.position;
    trace.ray.direction = canvas_to_viewport(camera, x, y, width, height);
    trace.ray.direction = vec3_rotate(trace.ray.direction, vec3_init(M_PI * camera.rotation.x / 180.0, M_PI * camera.rotation.y / 180, M_PI * camera.rotation.z / 180.0), 1);
    trace.ray.direction = vec3_normalize(trace.ray.direction);
    trace.depth = depth;
    trace.oc = oc;
    trace.mc = mc;
    trace.models = models;
    trace.objects = objects;
    trace.ambience = camera.ambience;

    trace.range = range_init(camera.viewport.distance, INFINITY);

    color = trace_ray(&trace, assets);

    output[id].x = color.x;
    output[id].y = color.y;
    output[id].z = color.z;
}
