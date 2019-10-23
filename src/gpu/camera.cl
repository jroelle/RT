t_vec3 canvas_to_viewport(t_camera camera, double x, double y, int width, int height)
{
    int x_center;
    int y_center;
    t_vec3 direction;

    x_center = width / 2;
    y_center = height / 2;

    direction.x = (x - x_center) * camera.viewport.delta.x;
    direction.y = -(y - y_center) * camera.viewport.delta.y;
    direction.z = camera.viewport.distance;

    return (direction);
}