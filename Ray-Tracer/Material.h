#pragma once

#include "Utility.h"
#include "Hittable.h"

struct hit_record;

class Material {
public:
	virtual bool scatter(const Ray& r_in, const hit_record& rec, Color& attenuation, Ray& scattered) const = 0;
};


class Lambertian : public Material {
public:
	Lambertian(const Color& a) : albedo(a) {}

	virtual bool scatter(const Ray& r_in, const hit_record& rec, Color& attenuation, Ray& scattered) const override {
		auto scatter_direction = rec.normal + random_unit_vector();

		if(scatter_direction.near_zero())
			scatter_direction = rec.normal;

		scattered = Ray(rec.p, scatter_direction);
		attenuation = albedo;
		return true;
	}

public:
	Color albedo;
};


class Metal : public Material {
public:
	Metal(const Color& a) : albedo(a) {}

	virtual bool scatter(const Ray& r_in, const hit_record& rec, Color& attenuation, Ray& scattered) const override {
	
		Vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
		scattered = Ray(rec.p, reflected);
		attenuation = albedo;
		return (dot(scattered.direction(), rec.normal) > 0);
	}

public:
	Color albedo;
};
