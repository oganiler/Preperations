# Rapid Interview Drill — 5 min

Answer out loud, ~60 seconds each. No notes. Then reveal.

1. **C++.** `std::vector<T>::push_back` invalidates iterators on reallocation, but
   `std::deque<T>::push_back` invalidates iterators while keeping *references* valid.
   Why the difference, and what does that imply about `std::deque`'s memory layout?

2. **Computer vision / ADAS.** Classical greedy NMS is O(n²) in the number of boxes.
   Name the two properties of the box set that decide whether that quadratic term actually
   matters at runtime, and give one way to make NMS bounded-latency for a safety-relevant
   perception path.

3. **Systems / performance.** You profile a ROS2 perception node and see high `perf`
   counts on `LLC-load-misses` inside a loop that walks a `std::vector<Detection>` where
   `Detection` is 96 bytes and you only read one `float` field. State the fix and the name
   of the general technique.

Answers sealed.
