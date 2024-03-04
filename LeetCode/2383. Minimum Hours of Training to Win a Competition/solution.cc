class Solution {
 public:
  int minNumberOfHours(int initialEnergy, int initialExperience,
                       vector<int>& energy, vector<int>& experience) {
    int required_hours = 0;
    int now_exp = initialExperience;
    int required_energy = std::accumulate(energy.begin(), energy.end(), 1);
    if (required_energy - initialEnergy > 0)
      required_hours = required_energy - initialEnergy;

    for (const int required_exp : experience) {
      if (now_exp <= required_exp) {
        required_hours += required_exp - now_exp + 1;
        now_exp = required_exp + 1;
      }
      now_exp += required_exp;
    }

    return required_hours;
  }
};