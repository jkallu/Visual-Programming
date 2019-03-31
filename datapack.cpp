#include "datapack.h"

DataPack::DataPack()
{
    createHeader();
    createSource();
}

void DataPack::createHeader()
{
    std::ofstream fileHeader("../nodegencodes/datapack.h");
    fileHeader << "#ifndef DATAPACK_H \n";
    fileHeader << "#define DATAPACK_H \n";
    fileHeader << "#include <stdio.h>\n";
    fileHeader << "#include <string.h>\n";
    fileHeader << "#include <stdlib.h>\n";

    fileHeader << "enum Types {Pack_Char, Pack_uChar, Pack_Int, Pack_uInt, Pack_Short, Pack_uShort, Pack_Long, Pack_uLong, Pack_Float, Pack_Double, Pack_lDouble, Pack_String};\n";
    fileHeader << "void pack_data(char *data, enum Types type, unsigned int size_in, void *in, unsigned int size_data_init);\n";
    fileHeader << "unsigned int pack_new_size(char *data, enum Types type, unsigned int size_in, unsigned int *old_size);\n";

    fileHeader << "#endif\n";
}

void DataPack::createSource()
{
    std::ofstream file("../nodegencodes/datapack.c");
    file << "#include \"datapack.h\"\n\n";
    file << "void pack_data(char *data, enum Types type, unsigned int size_in, void *in, unsigned int size_data_init)\n{\n";
    //file << "unsigned int size_data_init;\n";
    //file << "memcpy(&size_data_init, data, sizeof (unsigned int));\n";
    //file << "printf(\"INITIAL DATA ISZE %d \\n\", size_data_init);\n";
    file << "switch (type) {\n"
            "case Pack_Int:\n"
            "{\n"
                "size_in /= sizeof (int);\n"

                "printf(\"SIZE IN %d \\n\", size_in);\n"
                "memcpy(data + size_data_init, &size_in, sizeof (unsigned int));\n"
                "size_data_init += sizeof (size_in);\n"
                "enum Types typ = Pack_Int;\n"
                "memcpy(data + size_data_init , &typ, sizeof (Pack_Int));\n"
                "size_data_init += sizeof (typ);\n"
                "for(unsigned int i = 0; i < size_in; i++)\n"
                "{\n"
                    "int d = ((int*)in)[i];\n"
                    "memcpy(data + size_data_init , &d, sizeof (int));\n"
                    "size_data_init += sizeof (int);\n"
                "}\n"
                "unsigned int finalSize;\n"
                "memcpy(&finalSize, data, sizeof (unsigned int));\n"
                "printf(\"FINAL DATA ISZE %d \\n\", finalSize);\n"
                "break;\n"
            "}\n\n}\n";
    file << "char NV;\n"
            "memcpy(&NV, data + sizeof (unsigned int), sizeof (char));\n"
            "NV++;\n"
            "memcpy(data + sizeof (unsigned int), &NV, sizeof (char));\n";
    file << "}\n";

    file << "unsigned int pack_new_size(char *data, enum Types type, unsigned int size_in, unsigned int *old_size)\n{\n";
    file << "unsigned int size_data_init;\n";
    file << "memcpy(&size_data_init, data, sizeof (unsigned int));\n";
    file << "printf(\"INITIAL DATA ISZE %d \\n\", size_data_init);\n";
    file << "unsigned int newSize;\n";
    file << "switch (type) {\n"
            "case Pack_Int:\n"
            "{\n"
                "size_in /= sizeof (int);\n"
                "newSize = size_in * sizeof (int) + sizeof (unsigned int) + sizeof (Pack_Int);\n"
            "}\n\n}\n"
            "*old_size = size_data_init;"
            "return size_data_init + newSize;\n";

    file << "}";
}
