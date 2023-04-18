#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <filesystem>

const char* const a = "599Cc51887A8cb0C20F9CdE34cf9e0A535E5cAd1C26c7b562596ACC207Ae9A0bfB3E3161f31af5bEf1c2f064b3628174D83BF6E0739D9D6918fD9C2Eba02D5aD\0";
const char* const b = "0C3b676fe8d7188Cde022F71632830F36b98b181aD48Fed160006eA59\0";

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage: " << argv[0] << " input_file output_file" << std::endl;
        return 1;
    }

    const char* input = argv[1];
    const char* output = argv[2];

    // Extract the directory portion of the output file path, if available
    std::filesystem::path outputPath(output);
    std::string outputDir = ".";
    if (!outputPath.parent_path().empty())
    {
        outputDir = outputPath.parent_path().string();
    }

    // Create the output directory, if it does not exist
    std::filesystem::create_directories(outputDir);

    // Open the input and output files
    FILE* infile = fopen(input, "rb");
    FILE* outfile = fopen(output, "wb");

    if (infile == nullptr || outfile == nullptr)
    {
        std::cout << "Error opening files." << std::endl;
        return 1;
    }

    int dat, i = 0;
    while ((dat = fgetc(infile)) != EOF)
    {
        fputc(dat ^ a[i & 0x7F] ^ b[i % 57], outfile);
        i++;
    }

    fclose(infile);
    fclose(outfile);


	std::cout << "Done!\n";

    return 0;
}