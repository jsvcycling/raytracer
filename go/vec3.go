package main

import (
	"math"
	"math/rand"
)

type Vector3 struct {
	X float64
	Y float64
	Z float64
}

func NewVector3(x, y, z float64) Vector3 {
	return Vector3{x, y, z}
}

func Vector3_Rand() Vector3 {
	return Vector3{
		X: rand.Float64(),
		Y: rand.Float64(),
		Z: rand.Float64(),
	}
}

func Vector3_RandRange(low, high float64) Vector3 {
	return Vector3{
		X: RandRange(low, high),
		Y: RandRange(low, high),
		Z: RandRange(low, high),
	}
}

func (v Vector3) Add(v1 Vector3) Vector3 {
	return Vector3{
		X: v.X + v1.Y,
		Y: v.Y + v1.Y,
		Z: v.Z + v1.Z,
	}
}

func (v *Vector3) AddSelf(v1 Vector3) {
	*v = v.Add(v1)
}

func (v Vector3) Sub(v1 Vector3) Vector3 {
	return Vector3{
		X: v.X - v1.X,
		Y: v.Y - v1.Y,
		Z: v.Z - v1.Z,
	}
}

func (v *Vector3) SubSelf(v1 Vector3) {
	*v = v.Sub(v1)
}

func (v Vector3) Mul(f float64) Vector3 {
	return Vector3{
		X: v.X * f,
		Y: v.Y * f,
		Z: v.Z * f,
	}
}

func (v *Vector3) MulSelf(f float64) {
	*v = v.Mul(f)
}

func (v Vector3) Neg() Vector3 {
	return Vector3{
		X: -v.X,
		Y: -v.Y,
		Z: -v.Z,
	}
}

func (v Vector3) Dot(v1 Vector3) float64 {
	return v.X*v1.X + v.Y*v1.Y + v.Z*v1.Z
}

func (v Vector3) LengthSquared() float64 {
	return v.Dot(v)
}

func (v Vector3) Length() float64 {
	return math.Sqrt(v.LengthSquared())
}

func (v Vector3) Normalize() Vector3 {
	return v.Mul(1 / v.Length())
}

func Vector3_NewInUnitSphere() Vector3 {
	for {
		v := Vector3_RandRange(-1, 1)
		if v.LengthSquared() >= 1 {
			continue
		}
		return v
	}
}
