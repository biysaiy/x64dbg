#include "LogView.h"
#include "Configuration.h"

LogView::LogView(QWidget *parent) : QTextEdit(parent)
{
    QFont wFont("Monospace", 8);
    wFont.setStyleHint(QFont::Monospace);
    wFont.setFixedPitch(true);

    this->setFont(wFont);

    updateStyle();
    this->setUndoRedoEnabled(false);
    this->setReadOnly(true);

    connect(Bridge::getBridge(), SIGNAL(repaintTableView()), this, SLOT(updateStyle()));
    connect(Bridge::getBridge(), SIGNAL(addMsgToLog(QString)), this, SLOT(addMsgToLogSlot(QString)));
    connect(Bridge::getBridge(), SIGNAL(clearLog()), this, SLOT(clearLogSlot()));
}

void LogView::updateStyle()
{
    setStyleSheet(QString("QTextEdit { color: %1; background-color: %2 }").arg(ConfigColor("AbstractTableViewTextColor").name(), ConfigColor("AbstractTableViewBackgroundColor").name()));
}

void LogView::addMsgToLogSlot(QString msg)
{
    this->moveCursor(QTextCursor::End);
    this->insertPlainText(msg);
}


void LogView::clearLogSlot()
{
    this->clear();
}
