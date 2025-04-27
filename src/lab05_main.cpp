#include <array_list.h>
#include <iostream>
#include <array_list_utility.h>
#include <chrono>
#include <fstream>

int main(int argc, char** argv)
{
    // Now do our "stress test" -- generate a list of random floats of size 100 (and then of increasing sizes, step of 100 up to 1000000000)
    std::ofstream results_csv("..\\..\\docs\\lab05_raw_results.csv");
    // Reference: https://www.cplusplus.com/reference/random/
    std::default_random_engine generator;
    std::chrono::steady_clock::time_point start, end, absolute_start;
    std::chrono::milliseconds elapsed;
    std::chrono::nanoseconds elapsed_ns;
    std::chrono::minutes absolute_elapsed;
    absolute_start = std::chrono::steady_clock::now();

    // The number of values to save away for finding
    const float find_num = 1000;

    results_csv << "n, Create-time(ns), Shuffle-time(ns), Copy-time(ns), reserve-time(ns), QS-time(ms), BS-time(ms), BSearch-time(ns), LSearch-time(ns), Total-time(m)" << std::endl;

    const int max_sample_size = 1000000;   //1000000000*/
    const int max_bubblesort_size = 400000;   // bubble sort is SLOW -- we'll skip it over this
    for (int sample_size = 1000; sample_size < max_sample_size; sample_size += 5000)
    {
        // i. Create
        float percent_done = (float)sample_size / max_sample_size * 100.0f;
        std::cout << "SampleSize=" << sample_size << " (max=" << max_sample_size << ", " << percent_done << "% done)" << std::endl;
        std::cout << "=========================" << std::endl;
        results_csv << sample_size << ",";
        start = std::chrono::steady_clock::now();
        ssuds::ArrayList<float> AL;
        for (int i = 0; i < sample_size; i++)
            AL.append(i + 0.5f);
        end = std::chrono::steady_clock::now();
        elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        std::cout << "\tCreate time: " << elapsed_ns.count() << "ns" << std::endl;
        results_csv << elapsed_ns.count() << ",";

        // ii. Shuffle
        start = std::chrono::steady_clock::now();
        ssuds::shuffle(AL, true);
        end = std::chrono::steady_clock::now();
        elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        std::cout << "\tShuffle time: " << elapsed_ns.count() << "ns" << std::endl;
        results_csv << elapsed_ns.count() << ",";

        // iii. Make a copy of the shuffled array
        start = std::chrono::steady_clock::now();
        ssuds::ArrayList<float> AL_copy(AL);
        end = std::chrono::steady_clock::now();
        elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        std::cout << "\tCopy time: " << elapsed_ns.count() << "ns" << std::endl;
        results_csv << elapsed_ns.count() << ",";

        // iv. Save away some percentage of values.  The values are still unsorted,
        // so saving away the first find_percent% is just as good as any other
        start = std::chrono::steady_clock::now();
        ssuds::ArrayList<float> find_values;
        for (unsigned int i = 0; i < find_num; i++)
            find_values.append(AL[i]);
        end = std::chrono::steady_clock::now();
        elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        std::cout << "\tReserving time: " << elapsed_ns.count() << "ms" << std::endl;
        results_csv << elapsed_ns.count() << ",";

        // v. Quicksort AL
        std::cout << "\tQuicksort time: ";
        start = std::chrono::steady_clock::now();
        ssuds::quicksort(AL, ssuds::SortOrder::ASCENDING);
        end = std::chrono::steady_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << elapsed.count() << "ms" << std::endl;
        results_csv << elapsed.count() << ",";
       

        // vi. Sort AL_copy using bubble-sort
        /*if (sample_size < max_bubblesort_size)
        {
            std::cout << "\tBubble-sort time: ";
            start = std::chrono::steady_clock::now();
            ssuds::bubblesort(AL_copy, ssuds::SortOrder::ASCENDING);
            end = std::chrono::steady_clock::now();
            elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            std::cout << elapsed.count() << "ms" << std::endl;
            results_csv << elapsed.count() << ",";
        }
        else
            results_csv << ", ";*/

        // vii. Find reserved items with binary search
        std::cout << "\tBinary-search: ";
        start = std::chrono::steady_clock::now();
        for (unsigned int i = 0; i < find_values.size(); i++)
        {
            int garbage_index = ssuds::find_binary_search(AL, ssuds::SortOrder::ASCENDING, find_values[i]);
            if (find_values[i] != AL[garbage_index])
                std::cout << "found wrong value!\n";
        }
        end = std::chrono::steady_clock::now();
        elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        std::cout << elapsed_ns.count() << "ns" << std::endl;
        results_csv << elapsed_ns.count() << ",";

        // viii. Find our items with linear search (Lab2)
        std::cout << "\tLinear Search: ";
        start = std::chrono::steady_clock::now();
        for (unsigned int i = 0; i < find_values.size(); i++)
        {
            int garbage_index = AL.find(find_values[i]);
            if (find_values[i] != AL[garbage_index])
                std::cout << "found wrong value!\n";
        }
        end = std::chrono::steady_clock::now();
        elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        std::cout << elapsed_ns.count() << "ns" << std::endl;
        results_csv << elapsed_ns.count() << ",";

        // Show total elapsed time
        end = std::chrono::steady_clock::now();
        absolute_elapsed = std::chrono::duration_cast<std::chrono::minutes>(end - absolute_start);
        std::cout << "\tdone!  Total time so far = " << absolute_elapsed.count() << " minutes" << std::endl;
        results_csv << absolute_elapsed.count() << "\n";
    }


}