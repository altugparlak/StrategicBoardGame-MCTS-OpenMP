#include <iostream>
#include <vector>
#include <sstream>
#include <omp.h>

// Define a simple custom class
class CustomObject {
public:
    int id;
    std::string name;

    CustomObject(int id, const std::string& name) : id(id), name(name) {}

    std::string process() const {
        // Simulate some processing work and return a string with the result
        std::ostringstream oss;
        oss << "Processing object with ID: " << id << ", Name: " << name;
        return oss.str();
    }
};

int main(int argc, char* argv[]) {
    // Create a list of 10 CustomObject instances
    std::vector<CustomObject> objects;
    for (int i = 0; i < 10; ++i) {
        objects.emplace_back(i, "Object_" + std::to_string(i));
    }

    // Use 2 threads when creating OpenMP parallel regions
    omp_set_num_threads(10);

    // Vector to store results from each thread
    std::vector<std::string> results(objects.size());

    // Parallelize the for loop using the static schedule with chunks of 2 iterations
    #pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < objects.size(); ++i) {
        results[i] = "Thread " + std::to_string(omp_get_thread_num()) + " processes iteration " + std::to_string(i) + ".\n" + objects[i].process();
    }

    // Print all results after the parallel region
    for (const auto& result : results) {
        std::cout << result << std::endl;
    }

    return EXIT_SUCCESS;
}
