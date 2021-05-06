#include <cstdint>
#include <iostream>
#include <algorithm>
#include <vector>

struct Item final {
  int weight;
  int value;
};

double get_max_knapsack_value(int capacity, std::vector <Item> items) {
  double value = 0.0;

  std::sort(items.begin(), items.end(), [](const Item &rhs, const Item &lhs) {
      return static_cast<std::int64_t>(lhs.value) * rhs.weight <
             static_cast<std::int64_t>(lhs.weight) * rhs.value;
  });
  for (auto &item:items) {
    if (capacity > item.weight)
    {
      capacity -= item.weight;
      value += item.value;
    } else {
      value += item.value * (static_cast <double>(capacity) / item.weight);
      break;
    }
  }
  return value;
}

int main(void)
{
  std::ios_base::sync_with_stdio(false);
  int number_of_items;
  int knapsack_capacity;
  std::cin >> number_of_items >> knapsack_capacity;
  std::vector <Item> items(number_of_items);
  for (int i = 0; i < number_of_items; i++)
  {
    std::cin >> items[i].value >> items[i].weight;
  }

  double max_knapsack_value = get_max_knapsack_value(knapsack_capacity, std::move(items));

  std::cout.precision(3);
  std::cout << std::fixed << max_knapsack_value << std::endl;
  return 0;
}
