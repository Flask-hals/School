#include "image.h"
#include "window.h"
#include "load.h"
#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;
using std::unordered_map;

/**
 * Class that stores a summary of an image.
 *
 * This summary is intended to contain a high-level representation of the
 * important parts of an image. I.e. it shall contain what a human eye would
 * find relevant, while ignoring things that the human eye would find
 * irrelevant.
 *
 * To approximate human perception, we store a series of booleans that indicate
 * if the brightness of the image has increased or not. We do this for all
 * horizontal lines and vertical lines in a downsampled version of the image.
 *
 * See the lab instructions for more details.
 *
 * Note: You will need to use this data structure as the key in a hash table. As
 * such, you will need to implement equality checks and a hash function for this
 * data structure.
 */

const double threshold = 0.01;

class Image_Summary {
public:
    // Horizontal increases in brightness.
    vector<bool> horizontal;

    // Vertical increases in brightness.
    vector<bool> vertical;
};

namespace std {
    // Definiera en typ som specialiserar std::hash för vår typ:
    template <>
    class hash<Image_Summary> {
        public:
        // Typen ska kunna användas som ett funktionsobjekt.
        // Vi behöver därför överlagra funktionsanropsoperatorn (operator ()).
        size_t operator ()(const Image_Summary &to_hash) const {
            // Beräknar hash här med FNV-1 som passar till bits (0,1) och enkel implementation
            size_t h = 2166136261u;
            size_t prime = 16777619u;
            for (int i : to_hash.horizontal)
            {
                h *= prime;
                h ^= i;
            }

            for (int i : to_hash.vertical)
            {
                h *= prime;
                h ^= i;
            }

            return h;
        }
    };
}

// Compute an Image_Summary from an image. This is described in detail in the
// lab instructions.
Image_Summary compute_summary(const Image &image) {
    const size_t summary_size = 8;
    Image_Summary result;

    Image shrinkedImage = image.shrink(summary_size+1, summary_size+1);
    
    // Compare rows
    for (size_t y = 0; y < shrinkedImage.height(); y++) {
        for (size_t x = 0; x + 1 < shrinkedImage.width(); x++) {
            if (shrinkedImage.pixel(x, y).brightness() < shrinkedImage.pixel(x+1, y).brightness())
                result.horizontal.push_back(1);
            else
                result.horizontal.push_back(0);
        }
    }

    // Compare columns
    for (size_t y = 0; y + 1 < shrinkedImage.height(); y++) {
        for (size_t x = 0; x < shrinkedImage.width(); x++) {
            if (shrinkedImage.pixel(x, y).brightness() < shrinkedImage.pixel(x, y+1).brightness())
                result.vertical.push_back(1);
            else
                result.vertical.push_back(0);
        }
    }
    return result;
}

//operator==
inline bool operator==(const Image_Summary& lhs, const Image_Summary& rhs)
{
    return lhs.horizontal == rhs.horizontal && lhs.vertical == rhs.vertical;
}

int main(int argc, const char *argv[]) {
    WindowPtr window = Window::create(argc, argv);
    unordered_map<Image_Summary, vector<string>> um;

    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " [--nopause] [--nowindow] <directory>" << endl;
        cerr << "Missing directory containing files!" << endl;
        return 1;
    }

    vector<string> files = list_files(argv[1]);
    cout << "Found " << files.size() << " image files." << endl;

    if (files.size() <= 0) {
        cerr << "No files found! Make sure you entered a proper path!" << endl;
        return 1;
    }

    auto begin = std::chrono::high_resolution_clock::now();


    //loading the files and compute the summary for storaging
    for (const auto &file : files) {
        auto result = compute_summary(load_image(file));
        um[result].push_back(file);
        if (um[result].size() > 1)
        {
            window->report_match(um[result]); 
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    cout << "Total time: "
         << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()
         << " milliseconds." << endl;

    return 0;
}