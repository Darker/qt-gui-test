#include "results/SearchResult.h"
#include "results/WidgetResult.h"
#include "results/DialogResult.h"
#include "results/FileDialogResult.h"
#include "results/QMenuResult.h"
#include "results/QActionResult.h"
#include "results/QAbstractItemViewResult.h"
#include "results/QLineEditResult.h"
#include <memory>
#include <QLineEdit>
#include <QFileDialog>
void register_shit()
{
    SearchResult::Factory::registerConstructor(std::make_shared<WidgetResult::Factory>());
    SearchResult::Factory::registerConstructor<DialogResult, QDialog>();
    SearchResult::Factory::registerConstructor<FileDialogResult, QFileDialog>();
    SearchResult::Factory::registerConstructor<QMenuResult, QMenu>();
    SearchResult::Factory::registerConstructor<QActionResult, QAction>();
    SearchResult::Factory::registerConstructor<QAbstractItemViewResult, QAbstractItemView>();
    SearchResult::Factory::registerConstructor<QLineEditResult, QLineEdit>();
}
