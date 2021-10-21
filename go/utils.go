package main

import (
	"math/rand"
)

func Clamp(val, low, high float64) float64 {
	if val < low { return low }
	if val > high { return high }
	return val
}

func RandRange(low, high float64) float64 {
	return low + rand.Float64()*(high-low)
}
