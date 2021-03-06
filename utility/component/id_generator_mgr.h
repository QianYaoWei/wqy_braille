/*
 * =====================================================================================
 *
 *       Filename:  id_generator_mgr.h
 *
 *    Description:  id generator mgr
 *
 *        Created:  2016/10/27 16时36分07秒
 *       Compiler:  clang
 *
 *         Author:  TerenceWei 
 *          EMAIL:  360326661@qq.com
 *   Organization:  
 *
 * =====================================================================================
 */
#pragma once
#include <map>
#include "Singleton.h"
#include "TypeDefine.h"
#include "id_generator.h"

enum GeneratorType
{
    GeneratorType_Begin = 1,
    GeneratorType_BookMark = GeneratorType_Begin, // 书签

    GeneratorType_End
};

/*
 * =====================================================================================
 *        Class:  IDGeneratorMgr
 *  Description:  
 * =====================================================================================
 */
class IDGeneratorMgr : public utility::Singleton<IDGeneratorMgr>
{
public:
    IDGeneratorMgr ()
    {
    }

    bool Init();
    UInt64 GenID(GeneratorType type);

    IDGeneratorSptr FindGenerator(UInt32 type);

    IDGeneratorSptr CreateGenerator(UInt32 type);
private:
    std::map<UInt32, IDGeneratorSptr> _generators;
}; /* -----  end of class IDGeneratorMgr  ----- */

