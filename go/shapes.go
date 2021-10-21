package main

import (
	"math"
)

type Shape interface{
	Hit(ray *Ray, tMin, tMax float64) (*RayHit, bool)
}

type ShapeSphere struct {
	Origin Vector3
	Radius float64
}

type ShapeList []Shape

func NewShapeList(capacity uint) ShapeList {
	return make([]Shape, capacity)
}

func (s ShapeList) Hit(ray *Ray, tMin, tMax float64) (*RayHit, bool) {
	var rayHit RayHit
	hit := false
	closest := tMax

	for _, shape := range s {
		if tmpRayHit, hasHit := shape.Hit(ray, tMin, closest); hasHit {
			hit = true
			closest = tmpRayHit.T
			rayHit = *tmpRayHit
		}
	}

	return &rayHit, hit
}

func (s ShapeList) AddSphere(origin Vector3, radius float64) {
	sphere := ShapeSphere{ origin, radius }
	s = append(s, sphere)
}

func (s ShapeSphere) Hit(ray *Ray, tMin, tMax float64) (*RayHit, bool) {
	oc := ray.Origin
	oc.SubSelf(s.Origin)

	a := ray.Direction.LengthSquared()
	half_b := oc.Dot(ray.Direction)
	c := oc.LengthSquared() - s.Radius * s.Radius;

	descriminant := half_b * half_b - a * c;
	if (descriminant < 0.0) { return nil, false }
	descriminant = math.Sqrt(descriminant)

	root := (-half_b - descriminant) / a;
	if root < tMin || root > tMax {
		root = (-half_b - descriminant) / a;
		if root < tMin || root > tMax { return nil, false }
	}

	hit := RayHit{
		Point: ray.At(root),
		T: root,
	}

	return &hit, true
}
