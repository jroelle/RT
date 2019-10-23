float get_random(uint2 *seeds);
t_vec3 ray_random(t_vec3 v, double alpha, uint2 *seeds);

t_vec3 canvas_to_viewport(t_camera camera, double x, double y, int width, int height);

t_vec2 vec2_init(double x, double y);
t_vec3 vec3_init(double x, double y, double z);
t_vec3 vec3_div_n(t_vec3 v, double n);
t_vec3 vec3_mul_n(t_vec3 v, double n);
t_vec3 vec3_add_n(t_vec3 v, double n);
t_vec3 vec3_add_vec3(t_vec3 v1, t_vec3 v2);
t_vec2 vec2_sub_vec2(t_vec2 v1, t_vec2 v2);
t_vec3 vec3_sub_vec3(t_vec3 v1, t_vec3 v2);
t_vec3 vec3_mul_vec3(t_vec3 v1, t_vec3 v2);
double vec2_length(t_vec2 v);
double vec3_length(t_vec3 v);
t_vec2 vec2_normalize(t_vec2 v);
t_vec3 vec3_normalize(t_vec3 v);
double vec2_dot(t_vec2 v1, t_vec2 v2);
double vec3_dot(t_vec3 v1, t_vec3 v2);
double vec3_kdot(t_vec3 v1, t_vec3 v2, double k);
t_vec3 vec3_vec_mul(t_vec3 v1, t_vec3 v2);
t_vec3 vec3_cross(t_vec3 v1, t_vec3 v2);
int is_zero(t_vec3 v);
t_vec3 rot_x(t_vec3 v, t_vec3 rot, int invert);
t_vec3 rot_y(t_vec3 v, t_vec3 rot, int invert);
t_vec3 rot_z(t_vec3 v, t_vec3 rot, int invert);
t_vec3 vec3_rotate(t_vec3 v, t_vec3 rot, int invert);
double vec3_distance(t_vec3 v1, t_vec3 v2);

t_range range_init(double min, double max);

t_ray ray_init(t_vec3 position, t_vec3 direction);
t_vec3 ray_reflect(t_vec3 ray, t_vec3 normal);
t_vec3 ray_refract(t_vec3 ray, t_vec3 normal, double n1, double n2);

double triangle_square(double a, double b, double c);
double inside_triangle(t_vec3 p, t_vec3 a, t_vec3 b, t_vec3 c);
double reflection_coefficient(t_vec3 ray, t_vec3 normal, double n1, double n2);

int quadratic_solution_torus(double k[3], double dis[2]);
int quadratic_solution(double k[3], double dis[4]);
int cubic_solution(double k[4], double dis[4]);
void quartic_solution(double coef[5], double dis[4]);

t_hit closest_intersection(t_trace *trace, t_ray ray, t_range range, int ind, __global t_vec3 *assets);
void intersect_sphere(t_object obj, t_ray ray, double dis[4], __global t_vec3 *assets, t_trace *trace);
void intersect_plane(t_object obj, t_ray ray, double dis[4], __global t_vec3 *assets, t_trace *trace);
void intersect_cone(t_object obj, t_ray ray, double dis[4], __global t_vec3 *assets, t_trace *trace);
void intersect_cylinder(t_object obj, t_ray ray, double dis[4], __global t_vec3 *assets, t_trace *trace);
void intersect_disk(t_object obj, t_ray ray, double dis[4]);
void intersect_polygon(t_object obj, t_ray ray, double dis[4]);
void intersect_torus(t_object obj, t_ray ray, double dis[4]);
void intersect_paraboloid(t_object obj, t_ray ray, double dis[4]);
void intersect_hyperboloid(t_object obj, t_ray ray, double dis[4]);
void get_hit(t_hit *hit, double distances[4], t_range range, t_object obj, t_ray ray, int i, __global t_vec3 *assets);
void clip(t_object obj, t_ray ray, double *dis, t_trace trace);

double transparency_map(t_object obj, t_vec3 point, __global t_vec3 *assets);
void check_transparency(t_object obj, t_ray ray, double *dis, t_trace *trace, __global t_vec3 *assets);

void new_shade(t_trace *trace, t_shade *shader, __global t_vec3 *assets);
int get_random_light_model_index(t_trace *trace);
int get_random_light_object_index(t_trace *trace, int model_ind);
t_vec3 get_random_object_point(t_trace *trace, int obj_ind);
t_vec3 randomCosWeightedDirectionInHemisphere(t_trace *trace, t_vec3 nl);
void get_random_light_ray(t_trace *trace, t_shade *shader);
t_vec3 trace_ray(t_trace *trace, __global t_vec3 *assets);


t_vec3 texture(t_object obj, t_vec3 point, __global t_vec3 *assets);
t_vec3 texture_sphere(t_object obj, t_vec3 point, t_texture texture, __global t_vec3 *assets);
t_vec3 texture_torus(t_object obj, t_vec3 point, t_texture texture, __global t_vec3 *assets);
t_vec3 texture_cylinder(t_object obj, t_vec3 point, t_texture texture, __global t_vec3 *assets);
t_vec3 texture_cone(t_object obj, t_vec3 point, t_texture texture, __global t_vec3 *assets);
t_vec3 texture_plane(t_object obj, t_vec3 point, t_texture texture, __global t_vec3 *assets);

t_vec3 get_normal(t_object obj, t_ray ray, t_vec3 point, __global t_vec3 *assets);
t_vec3 normal_map(t_object obj, t_vec3 point, t_vec3 normal, __global t_vec3 *assets);
t_vec3 map_sphere(t_object obj, t_vec3 point, t_vec3 normal, __global t_vec3 *assets);
t_vec3 map_cylinder(t_object obj, t_vec3 point, t_vec3 normal, __global t_vec3 *assets);
t_vec3 map_plane(t_object obj, t_vec3 point, t_vec3 normal, __global t_vec3 *assets);
t_vec3 map_cone(t_object obj, t_vec3 point, t_vec3 normal, __global t_vec3 *assets);
t_vec3 wave(t_object obj, t_vec3 point, t_vec3 normal);
void clip(t_object obj, t_ray ray, double *dis, t_trace scene);

t_vec3 point_color(t_model model, t_object obj, t_vec3 point, __global t_vec3 *assets);

double smootherstep(double x);
double lerp(double a, double b, double t);
t_vec3 get_noise(__global t_vec3 *noise, int x, int y, t_texture texture);
t_vec3 choose_procedural_texture(__global t_vec3 *noise, int proc_tex, int x, int y, t_texture texture);
t_vec3 procedural_texture_sphere(__global t_vec3 *noise, t_object obj, t_vec3 point);
t_vec3 procedural_texture_plane(__global t_vec3 *noise, t_object obj, t_vec3 point);
t_vec3 procedural_texture_cylinder(__global t_vec3 *noise, t_object obj, t_vec3 point);
t_vec3 procedural_texture_cone(__global t_vec3 *noise, t_object obj, t_vec3 point);
t_vec3 chess_board(int x, int y, t_texture texture);
t_vec3 brick_wall(int x, int y, t_texture texture);
t_vec3 procedural_texture(t_object obj, t_vec3 point, __global t_vec3 *noise);