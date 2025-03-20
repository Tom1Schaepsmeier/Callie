#include <string>
#include "../obsidian_task.h"

class MarkdownWriter {

    public:
        MarkdownWriter();

        MarkdownWriter(const MarkdownWriter& markdown_writer);

        MarkdownWriter(MarkdownWriter&& markdown_writer);

        ~MarkdownWriter();
}