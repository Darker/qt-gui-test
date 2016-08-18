#include "results/SearchResult.h"
#include "results/WidgetResult.h"
#include "results/DialogResult.h"
#include "results/FileDialogResult.h"
#include <memory>
void register_shit()
{
    SearchResult::Factory::registerConstructor(std::make_shared<WidgetResult::Factory>());
    SearchResult::Factory::registerConstructor(
                std::make_shared<SearchResult::FactorySimple<DialogResult, QDialog>>()
    );
    SearchResult::Factory::registerConstructor(
                std::make_shared<SearchResult::FactorySimple<FileDialogResult, QFileDialog>>()
    );
}
