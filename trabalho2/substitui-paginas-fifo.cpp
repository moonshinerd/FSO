#include <cstdio>
#include <deque>
#include <algorithm>

int main() {
    int max_size, total_pages, current_page, faults = 0;
    scanf("%d\n%d\n%d", &max_size, &total_pages, &current_page);

    std::deque<int> cache;
    cache.push_back(current_page);
    faults++, total_pages--;

    while (total_pages) {
        scanf("%d", &current_page);

        if (std::find(cache.begin(), cache.end(), current_page) == cache.end()) {
            if (cache.size() < max_size) {
                cache.push_back(current_page);
            } else {
                cache.pop_front();
                cache.push_back(current_page);
            }
            faults++;
        }
        total_pages--;
    }

    printf("%d\n", faults);
    return 0;
}
