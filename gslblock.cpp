#include "gslblock.h"
#include "string"

GSLBlock::GSLBlock(int i, BlockItem::BlockType type):
    BlockIO(i, 1, 1, type)
{

}

void GSLBlock::init()
{
    lblData->setVisible(false);
    teData->setVisible(false);

    boxLayout->rowStretch(1);

    groupBox->setLayout(boxLayout);
    groupBox->setTitle("GSL Block");
}

void GSLBlock::generateCode(QString dir)
{
    std::string compiledExp  = "d";

    std::ofstream fileHeader(QString(dir+leName->text()).toLatin1()+".h");
    QString upper = leName->text().toUpper();
    fileHeader << "#ifndef " << upper.toStdString() << "_H \n";
    fileHeader << "#define " << upper.toStdString() << "_H \n";

    fileHeader << "void * " << leName->text().toStdString() << "(void *dat);\n";
    fileHeader << "#endif\n";

    fileHeader.close();

    std::ofstream file(QString(dir+leName->text()).toLatin1()+".c");
    file << "#include \"" << leName->text().toStdString() << ".h\"\n";
    file << "#include \"linkedList.h\"\n";
    file << "#include \"packer.h\"\n";
    file << "#include <string.h>\n";
    file << "#include <math.h>\n"
            "#include <gsl/gsl_math.h>\n"
            "#include <gsl/gsl_errno.h>\n"
            "#include <gsl/gsl_odeiv2.h>\n";
    file << "#include <stdio.h>\n\n";
    file << "extern pthread_mutex_t lock;\n"
            "extern PData_t *gPData;\n"
            "char *global_data;\n\n"
            ;
    file << "int dfunc (double t, const double y[], double f[], void *params_ptr) \n{\n"
            "double *lparams = (double *) params_ptr;\n"
            "double alpha = lparams[0];\n"
            "double omega = lparams[1];\n"
            "f[0] = alpha * y[0] * (1+ sin (omega*t));\n"
            "return GSL_SUCCESS; \n"
            "}\n";
    file << "void * " << leName->text().toStdString() << "(void *dat) \n{\n";
    file << "while(pthread_mutex_trylock(&global_lock))\n"
            "{\n"
            "printf(\"\\rTRYING TO LOCK MUTEX %s\", __FUNCTION__);\n"
            "}\n";
    file << "char **ptr_global_data = &global_data;\n"
            "size_t tot_size;\n"
            "memcpy(&tot_size, *ptr_global_data, sizeof (tot_size));\n"
            "char *data = mallocAndCheck(tot_size);\n"
            "memcpy(data, *ptr_global_data, tot_size);\n\n"
            "free(*ptr_global_data);\n"
            "*ptr_global_data = NULL;\n"
            "pthread_mutex_unlock(&global_lock);\n\n"
            ;
    file << "char **callFunc = mallocAndCheck(" << numOfOutputs << "* sizeof (char *));\n"
            "char **data_out = mallocAndCheck(" << numOfOutputs << "* sizeof (char *));\n"
            ;
    file << "const int dimension = 1; \n"
            "int status; \n"
            "const double eps_abs = 1.e-8;  \n"
            "const double eps_rel = 1.e-10; \n"
            "double alpha = 0.015;	\n"
            "double omega = 2.0*M_PI/365.0; \n"
            "double myparams[2];   \n"
            "double y[dimension]; \n"
            "double h = 1.0e-6; \n"
            "gsl_odeiv2_system ode_system;	\n"
            "myparams[0] = alpha;  \n"
            "myparams[1] = omega; \n"
            "ode_system.function = dfunc;  \n"
            "ode_system.dimension = dimension; \n"
            "ode_system.params = myparams; \n"
            "y[0] = 2.0; \n"
            "gsl_odeiv2_driver * drv = gsl_odeiv2_driver_alloc_y_new (&ode_system, gsl_odeiv2_step_rkf45, h, eps_abs, eps_rel); \n"
            "double t, t_next; \n"
            ;
    file << "enum Types type;\n"
            "char *in = NULL;\n"
            "size_t size;\n"
            "getData(0, data, &type, &size, &in);\n"
            "size_t add = 0;\n"
            "if(type == Pack_Int)\n"
            "{\n"
                "for(size_t i = 0; i < size; i++)\n"
                "{\n"
                    "int d;\n"
                    "memcpy(&d, in + add, sizeof (int));\n"
                    //"d = " << leExpression->text().toStdString() <<"((double)d);\n"
                    "d = " << compiledExp << ";\n"
                    "memcpy(in + add, &d, sizeof (int));\n"
                    "add += sizeof (int);\n"
                "}\n"
            "}\n"
            "else if(type == Pack_Float)\n"
            "{\n"
                "if(size > 0) \n { \n"
                "memcpy(&t, in + add, sizeof (float));\n"
                "add += sizeof (float);\n"
                "}\n"
                "for(size_t i = 1; i < size; i++)\n"
                "{\n"
                    "float d;\n"
                    "memcpy(&d, in + add, sizeof (float));\n"
                    //"d =  " << leExpression->text().toStdString() <<"((double)d);\n"
                    "status = gsl_odeiv2_driver_apply (drv, &t, d, y); \n"
                    "if (status != GSL_SUCCESS) { \n"
                    "    printf (\"Error: status %d\\n\", status); \n"
                    "    break;  \n"
                    "}  \n"
                    "d = " << "y[0]" << ";\n"
                    "memcpy(in + add, &d, sizeof (float));\n"
                    "add += sizeof (float);\n"
                "}\n"
            "}\n"
            "else if(type == Pack_Double)\n"
            "{\n"
                "for(size_t i = 0; i < size; i++)\n"
                "{\n"
                    "double d;\n"
                    "memcpy(&d, in + add, sizeof (double));\n"
                    //"d =  " << leExpression->text().toStdString() <<"(d);\n"
                    "d = " << compiledExp << ";\n"
                    "memcpy(in + add, &d, sizeof (double));\n"
                    "add += sizeof (double);\n"
                "}\n"
            "}\n"
            ;
    for(int i = 0; i < numOfOutputs; i++)
    {
        file << "char nm_" << i << "[] = \"" << lblOutConToBlock[i]->text().toStdString() <<"\";\n";
        file << "callFunc[" << i << "] = mallocAndCheck(sizeof (nm_" << i << ") + 1);\n";
        file << "memcpy(callFunc[" << i << "], nm_" << i << ", sizeof (nm_" << i << ") + 1);\n"
                "data_out[" << i << "] = NULL;\n"
                "packData(&data_out[" << i << "], -1, Pack_func, strlen (callFunc[" << i << "]) + 1, callFunc[" << i << "]);\n"
                "packData(&data_out[" << i << "], " << conToIONum[i] << ", type, size, in);\n"

                "localProcedureCall(callFunc[" << i << "], " << conToTotIns[i] << ", 1, data_out[" << i << "]);\n\n";

        file << "if(data_out[" << i << "] != NULL)\n{\n"
                "free(data_out[" << i << "]);\n}\n"
                "if(callFunc[" << i << "] != NULL)\n{\n"
                "free(callFunc[" << i << "]);\n}\n\n"
                ;
    }
    file << "if(data_out != NULL)\n{\n"
            "free(data_out);\n}\n"
            "if(callFunc != NULL)\n{\n"
            "free(callFunc);\n}\n\n"
            "if(data != NULL)\n{\n"
            "free(data);\n}\n\n"
            "if(in != NULL)\n{\n"
            "free(in);\n}\n\n"
            ;
    file << "printf(\""<<leName->text().toStdString()<<" END\\n\");\n";
    file << "gsl_odeiv2_driver_free (drv);\n";
    file << "pthread_exit(NULL);\n"
            "}";
    file.close();
}
