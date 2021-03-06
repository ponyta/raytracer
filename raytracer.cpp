#include <iostream>
#include "vec3.h"
#include "ray.h"

using namespace std;

bool hit_sphere(const vec3& center, float radius, const ray& r) {
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = 2.0*dot(oc, r.direction());
    float c = dot(oc, oc) - (radius*radius);
    float discriminant = b*b - 4*a*c;
    return (discriminant > 0);
}

vec3 color(const ray& r) {
    if (hit_sphere(vec3(0, 0, -1), 0.5, r)) {
        return vec3(1, 0, 0);
    } else {
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5*(unit_direction.y() + 1.0); // (-1, 1) to (0, 1)
        return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0); // lerp from white to light blue
    }
}

int main() {
    int nx = 1024;
    int ny = 768;

    cout << "P3\n" << nx << " " << ny << "\n255\n";
    vec3 top_left_corner(-2.0, 1.5, -1.0); // 4 x 3 aspect ratio
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, -3.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);
    for (int j = 0; j < ny; j++) {
        for (int i = 0; i < nx; i++) {
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
            ray r(origin, top_left_corner + u*horizontal + v*vertical);
            vec3 col = color(r);
            int ir = int(255.99 * col.r());
            int ig = int(255.99 * col.g());
            int ib = int(255.99 * col.b());
            cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}
