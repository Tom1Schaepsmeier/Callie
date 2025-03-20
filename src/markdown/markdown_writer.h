#include <filesystem>
#include <fstream>
#include <string>

#include "../obsidian_task.h"

class MarkdownWriter {
    std::string mFile_path

    public:

        /*
        Default constructor

        @param filepath (string) - the absolute filepath to the file which should be worked on
        */
        MarkdownWriter(std::string filepath);

        /*
        Copy Constructor

        @param markdown_writer (MarkdownWriter&) - 
        */
        MarkdownWriter(const MarkdownWriter& markdown_writer);

        /*
        Move Constructor

        @param markdown_writer (MarkdownWriter&&) - 
        */
        MarkdownWriter(MarkdownWriter&& markdown_writer);

        /*
        Destructor
        */
        ~MarkdownWriter();

        /*
        Writes a new line at the end of the stored file

        @param input_strem (string) - contains the content which will be appended to the file
        */
        void write_line(std::string input_stream);

        /*
        Deletes the line
        TODO
        */
        void delete_line()
}