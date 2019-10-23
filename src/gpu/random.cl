float get_random(uint2 *seeds)
{
    seeds->x = 36969 * ((seeds->x) & 65535) + ((seeds->x) >> 16);
    seeds->y = 18000 * ((seeds->y) & 65535) + ((seeds->y) >> 16);

    unsigned int ires = ((seeds->x) << 16) + (seeds->y);

    union {
        float f;
        unsigned int ui;
    } res;

    res.ui = (ires & 0x007fffff) | 0x40000000;
    return (res.f - 2.0f) / 2.0f;
}

t_vec3 ray_random(t_vec3 v, double alpha, uint2 *seeds)
{
    t_vec3 ray;
    double cos_theta;
    double sin_theta;
    double phi;
    t_vec3 tangent_space_dir;
    t_vec3 helper;
    t_vec3 tangent;
    t_vec3 binormal;

    cos_theta = pow((double)get_random(seeds), 1.0 / (alpha + 1.0));
    sin_theta = sqrt(1.0 - cos_theta * cos_theta);
    phi = 2 * M_PI * (double)get_random(seeds);

    tangent_space_dir = vec3_init(cos(phi) * sin_theta, sin(phi) * sin_theta, cos_theta);
    helper = vec3_init(1.0, 0.0, 0.0);
    if (fabs(v.x) > 0.99)
        helper = vec3_init(0.0, 0.0, 1.0);
    tangent = vec3_normalize(vec3_vec_mul(v, helper));
    binormal = vec3_normalize(vec3_vec_mul(v, tangent));

    ray.x = tangent_space_dir.x * tangent.x +
            tangent_space_dir.y * binormal.x +
            tangent_space_dir.z * v.x;
    ray.y = tangent_space_dir.x * tangent.y +
            tangent_space_dir.y * binormal.y +
            tangent_space_dir.z * v.y;
    ray.z = tangent_space_dir.x * tangent.z +
            tangent_space_dir.y * binormal.z +
            tangent_space_dir.z * v.z;

    return (ray);
}
