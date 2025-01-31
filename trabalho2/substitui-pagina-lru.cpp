#include <cstdio>
#include <deque>
#include <algorithm>

void updateCache(std::deque<int> &cache, int recent) {
    auto position = std::find(cache.begin(), cache.end(), recent);
    std::rotate(position, position + 1, cache.end());
}

int main() {
    int cache_size, total_pages, current_page, faults = 0;
    scanf("%d\n%d\n%d", &cache_size, &total_pages, &current_page);

    std::deque<int> page_cache;
    page_cache.push_back(current_page);
    faults++, total_pages--;

    while (total_pages) {
        scanf("%d", &current_page);

        if (std::find(page_cache.begin(), page_cache.end(), current_page) == page_cache.end()) {
            if (page_cache.size() < cache_size) {
                page_cache.push_back(current_page);
            } else {
                page_cache.pop_front();
                page_cache.push_back(current_page);
            }
            faults++;
        } else {
            updateCache(page_cache, current_page);
        }
        total_pages--;
    }

    printf("%d\n", faults);
    return 0;
}
