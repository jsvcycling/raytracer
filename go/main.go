package main

import (
	"math/rand"
)

func main() {
	// Image
	aspectRatio := float64(16.0 / 9.0)
	imageWidth := 1280
	imageHeight := int(float64(imageWidth) / aspectRatio)
	samplesPerPixel := 10
	maxDepth := 50

	// Camera
	camera := NewCamera()

	// World
	world := NewShapeList(64)
	world.AddSphere(NewVector3(0, 0, -1), 0.5)
	world.AddSphere(NewVector3(0, -100.5, -1), 100)

	for j := imageHeight; j >= 0; j-- {
		for i := 0; i < imageWidth; i++ {
			pixelColor := NewVector3(0, 0, 0)

			for s := 0; s < samplesPerPixel; s++ {
				u := (float64(i) + rand.Float64()) / float64(imageWidth - 1)
				v := (float64(j) + rand.Float64()) / float64(imageHeight - 1)

				ray := camera.GetRay(u, v)
				pixelColor.AddSelf(ray.CalcColor(world, maxDepth))
			}
		}
	}
}
