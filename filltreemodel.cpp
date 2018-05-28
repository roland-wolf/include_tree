#include "filltreemodel.h"

#include "treeitem.h"
#include "parsepreprocessed.h"


void recursiveTreeBuilder( const SourceFile &sourceFile, TreeItem *treeItem, int depth )
{
    depth++;
    for(const auto & subSource : sourceFile.includes) {
        QVariantList variantList {subSource.fileName, subSource.netLines, subSource.indirectLines};
        TreeItem *newItem = new TreeItem( variantList, treeItem);
        recursiveTreeBuilder(subSource, newItem, depth);
    }
}


TreeItem *fillTreeModel(const SourceFile &sourceFile)
{
    QVariantList items {"Tree", "Direct", "Indirect"};
    TreeItem *rootItem= new TreeItem(items);
    QVariantList variantList {sourceFile.fileName, sourceFile.netLines, sourceFile.indirectLines};
    TreeItem *firstLevel = new TreeItem(variantList, rootItem );
    recursiveTreeBuilder(sourceFile, firstLevel, 0);
    return rootItem;
}



