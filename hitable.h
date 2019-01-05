#pragma once
#ifndef HITABLE
#define HITABLE
#define _USE_MATH_DEFINES

#include "ray.h"
#include "aabb.h"
#include <cmath>

class material;

struct hit_record
{
	float t;
	vec3 p;
	vec3 normal;
	material *mat_ptr;
	float u;
	float v;
};


class hitable
{
public:
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
	virtual bool bounding_box(float t0, float t1, aabb& box) const = 0;

};

void get_sphere_uv(const vec3& p, float& u, float& v) {
	float phi = atan2(p.z(), p.x());
	float theta = asin(p.y());
	u = 1 - (phi + M_PI) / (2 * M_PI);
	v = (theta + M_PI / 2) / M_PI;
}

class xy_rect :public hitable {
public:
	xy_rect(){}
	xy_rect(float _x0, float _x1, float _y0, float _y1, float _k, material *mat) :
		x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k), mp(mat) {};
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
	virtual bool bounding_box(float t0, float t1, aabb& box) const {
		box = aabb(vec3(x0, y0, k - 0.0001), vec3(x1, y1, k + 0.0001));
		return true;
	}
	material *mp;
	float x0, x1, y0, y1, k;
};

class xz_rect :public hitable {
public:
	xz_rect() {}
	xz_rect(float _x0, float _x1, float _z0, float _z1, float _k, material *mat) :
		x0(_x0), x1(_x1), z0(_z0), z1(_z1), k(_k), mp(mat) {};
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
	virtual bool bounding_box(float t0, float t1, aabb& box) const {
		box = aabb(vec3(x0, k - 0.0001, z0), vec3(x1, k + 0.0001, z1));
		return true;
	}
	material *mp;
	float x0, x1, z0, z1, k;
};


class yz_rect :public hitable {
public:
	yz_rect() {}
	yz_rect(float _y0, float _y1, float _z0, float _z1, float _k, material *mat) :
		y0(_y0), y1(_y1), z0(_z0), z1(_z1), k(_k), mp(mat) {};
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
	virtual bool bounding_box(float t0, float t1, aabb& box) const {
		box = aabb(vec3(k - 0.0001, y0, z0), vec3(k + 0.0001, y1, z1));
		return true;
	}
	material *mp;
	float y0, y1, z0, z1, k;
};
#endif

