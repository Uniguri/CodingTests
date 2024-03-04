#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

using ll = long long int;

map<tuple<int, ll, ll>, int> cache;

ll subsolution(int n, ll l, ll r) {
  if (n < 1 || l < 0 || r < 0) return 0;
  if (n == 1) {
    if (l <= 2 && 2 <= r) return r - l;
    return r - l + 1;
  }

  if (cache.find({n, l, r}) != cache.end()) return cache[{n, l, r}];

  const ll ratio = pow(5, n - 1);
  ll answer = 0, s = l / ratio, e = r / ratio;
  if (s == e)
    answer += subsolution(n - 1, l - s * ratio, r - e * ratio);
  else {
    if (s != 2) answer += subsolution(n - 1, l - s * ratio, ratio - 1);
    if (e != 2) answer += subsolution(n - 1, 0, r - e * ratio);
    const ll power = pow(4, n - 1);
    for (ll i = s + 1; i < e; ++i) {
      if (i == 2) continue;
      answer += power;
    }
  }
  cache[{n, l, r}] = answer;

  return answer;
}

ll solution(int n, long long l, long long r) {
  ll answer = subsolution(n, --l, --r);
  return answer;
}