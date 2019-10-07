/*
 * PerlinNoise.h
 *
 *  Created on: 20.11.2016
 *      Author: Kevin
 */
/***
 *
 * Copyright (C) 2016 DaeFennek
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
***/

#pragma once

class PerlinNoise {
public:

  // Constructor
    PerlinNoise();
    PerlinNoise(double _persistence, double _frequency, double _amplitude, int _octaves, int _randomseed);
    PerlinNoise(const PerlinNoise&) = delete;
    PerlinNoise(PerlinNoise&&) = delete;
    void operator=(const PerlinNoise&) = delete;
    void operator=(PerlinNoise&&) = delete;

  // Get Height
    double GetHeight(double x, double y) const;

  // Get
  double Persistence() const { return persistence; }
  double Frequency()   const { return frequency;   }
  double Amplitude()   const { return amplitude;   }
  int    Octaves()     const { return octaves;     }
  int    RandomSeed()  const { return randomseed;  }

  // Set
  void Set(double _persistence, double _frequency, double _amplitude, int _octaves, int _randomseed);

  void SetPersistence(double _persistence) { persistence = _persistence; }
  void SetFrequency(  double _frequency)   { frequency = _frequency;     }
  void SetAmplitude(  double _amplitude)   { amplitude = _amplitude;     }
  void SetOctaves(    int    _octaves)     { octaves = _octaves;         }
  void SetRandomSeed( int    _randomseed)  { randomseed = _randomseed;   }

private:

    double Total(double i, double j) const;
    double GetValue(double x, double y) const;
    double Interpolate(double x, double y, double a) const;
    double Noise(int x, int y) const;

    double persistence, frequency, amplitude;
    int octaves, randomseed;
};
