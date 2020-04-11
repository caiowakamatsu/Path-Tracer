//
// Created by legend on 4/9/20.
//

#include "Material.h"
#include <cmath>

Material::Material(Vector3 c, float r, float a, bool re, float index) {
    colour = c;
    roughness = r;
    absorb = a;
    refract = re;
    ref_index = index;
}

void Material::getMaterialRay(Ray& ray) {
    if(roughness > 0){
        Vector3 point = Vector3(drand48() * 2 - 1, drand48() * 2 - 1, drand48() * 2 - 1);
        point = point.toUnitVector();
        ray.direction.mix(point, roughness);
    }
}

void Material::getRefractiveRay(Ray& ray, Vector3& normal, HitRecord& rec){
    Vector3 rayDirection = ray.direction;
    Vector3 outNormal;
    float nit;
    float cosine;
    if(ray.direction.dot(normal) > 0){
        outNormal = normal * -1;
        nit = ref_index;
        cosine = ray.direction.dot(normal) /
                ray.direction.length() * ref_index;
    } else {
        outNormal = normal;
        nit = 1.0f / ref_index;
        cosine = -ray.direction.dot(normal) / ray.direction.length();
    }
    ray.direction.refract(outNormal, ref_index);
    Vector3 offset = outNormal * 0.0001f;
    ray.origin = rec.intersectionPoint + offset;
}

bool Material::canrefract(Vector3& v, Vector3& n, float nit, Vector3& ref) {
    Vector3 uv = v.toUnitVector();
    float dt = uv.dot(n);
    float disc = 1.0 - nit*nit*(1-dt*dt);
    if(disc > 0){
        Vector3 a = n * dt;
        a = uv - a;
        a = a * nit;
        a -= n;
        ref = a * sqrtf(disc);
        return true;
    }
    return false;
}

/*
 *         let reflected = ray_in.direction.normalize().reflect(record.normal);
        let scattered;
        let outward_normal;
        let ni_over_nt;

        let reflect_prob;
        let cosine;

        if ray_in.direction.dot(record.normal) > 0.0 {
            outward_normal = -record.normal;
            ni_over_nt = self.refractive_index;
            cosine = ray_in.direction.dot(record.normal) / ray_in.direction.length()
                * self.refractive_index;
        } else {
            outward_normal = record.normal;
            ni_over_nt = 1.0 / self.refractive_index;
            cosine = -ray_in.direction.dot(record.normal) / ray_in.direction.length();
        }

        let refracted = ray_in.direction.refract(outward_normal, ni_over_nt);
        let attenuation = Vector3::new(1.0, 1.0, 1.0);

        if refracted != Vector3::default() {
            reflect_prob = schlick(cosine, self.refractive_index);
        } else {
            reflect_prob = 1.0;
        }

        if random_float() < reflect_prob {
            scattered = Ray::with_time(record.p, reflected, ray_in.time);
        } else {
            scattered = Ray::with_time(record.p, refracted, ray_in.time);
        }

        Some((scattered, attenuation))
 */
