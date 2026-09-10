# Rapid Interview Drill — 5 min

Answer out loud, ~60 seconds each. No notes. Then reveal.

1. **C++.** A function returns `std::vector<T>` by value. Explain what actually happens in
   C++17 — no copy, a move, or neither — and note where the answer differs between
   `return std::vector<T>{...};` and `return result;` for a named local. Name both distinct
   language mechanisms involved.

2. **Computer vision.** Define semantic, instance and panoptic segmentation precisely enough
   that the boundaries are unambiguous. Then say which one a motion planner actually needs
   and why the other two are insufficient on their own.

3. **Systems / performance.** You have a 4 MP single-channel `uint8` image in a row-major
   buffer and you iterate it column-major by mistake. Quantify the cost — not "it's slower",
   but the mechanism and the rough factor — and state the image width at which a second,
   distinct hardware effect kicks in and makes it dramatically worse.

Answers sealed.
