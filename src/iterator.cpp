#include "iterator.h"
#include "node.h"
#include "folder.h"

#include <list>

FolderIterator::FolderIterator(Folder * composite): _composite(composite) {}

