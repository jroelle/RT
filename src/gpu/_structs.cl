#pragma OPENCL EXTENSION cl_khr_fp64 : enable

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"

#define TEXTURE_WIDTH 1024
#define TEXTURE_HEIGHT 1024

typedef struct s_vec2
{
    double x;
    double y;
} t_vec2;

typedef struct s_vec3
{
    double x;
    double y;
    double z;
} t_vec3;

typedef struct s_hit
{
    int index;
    double distance;
    t_vec3 normal;
    t_vec3 point;
} t_hit;

typedef struct s_range
{
    double min;
    double max;
} t_range;

typedef struct s_ray
{
    t_vec3 position;
    t_vec3 direction;
} t_ray;

typedef struct s_viewport
{
    double width;
    double height;
    double distance;
    t_vec2 delta;
} t_viewport;

typedef struct s_camera
{
    t_vec3 position;
    t_vec3 rotation;
    t_viewport viewport;
    t_vec3 ambience;
} t_camera;

typedef struct s_texture
{
    double		scale;
    int			index;
    unsigned	position;
	unsigned	width;
	unsigned	height;
    int			dx;
    int			dy;
} t_texture;

typedef struct s_object
{
    int type;
    int active;
    t_vec3 position;
    t_vec3 odirection;
    t_vec3 direction;
    double angle;
    double radius;
    t_vec3 a;
    t_vec3 b;
    t_vec3 c;
    int model_index;
    double minor_radius;
    double major_radius;
    double opacity;
    t_vec3 surface;
    int boolean;
    int proc_tex;
    int wave;
    t_texture texture;
    t_texture map;
    t_texture transparency;
} t_object;

typedef struct s_model
{
    double specular;
    double reflective;
    double light;
    double refractive_index;
    t_vec3 color;
    t_vec3 rotation;
    t_vec3 position;
    int clip;
    int active;
} t_model;

typedef struct s_shade
{
    t_vec3 accumCol;
    t_vec3 maskEyePath;
    t_vec3 maskLightPath;
    t_vec3 eyeX;
    t_vec3 lightX;
    t_vec3 nlEyePath;
    t_vec3 nlLightPath;
    t_vec3 lightEmission;
    t_vec3 lightPoint;
    t_ray lightRay;
    t_ray connectRay;
    int eyeIndex;
    int lightObejctIndex;
    int lightModelIndex;
    int bounceIsSpecular;
    int skipConnectionLightPath;
    int diffuseCount;
    int previousIntersecType;
    int state;
    int stack[20];
} t_shade;

typedef struct s_trace
{
    int id;
    double x;
    double y;
    __global t_model *models;
    __global t_object *objects;
    int oc;
    int mc;
    t_ray ray;
    t_range range;
    int depth;
    uint2 seeds;
    t_vec3 ambience;
} t_trace;

