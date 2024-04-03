#ifndef calc_H
#define calc_H

double _base, _factor;

double inline map2(const double value, double _inMin, double _inMax, double _outMin, double _outMax) {
  double _inRange = _inMax - _inMin;
  double _outRange = _outMax - _outMin;
  if (_inRange == 0.0 || _outRange == 0.0) return 0;

  _factor = _outRange / _inRange;
  _base = _outMin - _inMin * _factor;

  if ( value <= _inMin ) return _outMin;
  if ( value >= _inMax ) return _outMax;

  return _base + value * _factor;
}

#endif
