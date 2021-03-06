#include <iostream>
#include "id_generator_mgr.h"
#include "orm_db_callback.h"

bool IDGeneratorMgr::Init()
{
    for (UInt32 i = GeneratorType_Begin; i < GeneratorType_End; ++i) {
        _generators[i];
    }

    IDGenerator generator;
    SelectOrmDBCallBack<IDGenerator> callback;

    generator.SelectFromDB("glob_id", &callback);
    while (!callback.Empty()) {
        auto sptr = callback.GetNext();
        _generators[sptr->GetID()] = sptr;
        std::cout<<sptr->GetID()<<":"<<sptr->Get_curID()<<std::endl;
    }

    return true;
}

UInt64 IDGeneratorMgr::GenID(GeneratorType type)
{
    auto itr = _generators.find(type);
    if (itr != _generators.end()) {

        if (itr->second) {
            return itr->second->GenerateID();
        }
        else {
            auto sptr = CreateGenerator(type);
            if (sptr) {
                return sptr->GenerateID();
            }

            return 0;
        }
    }
    else {
        return 0;
    }
}

IDGeneratorSptr IDGeneratorMgr::CreateGenerator(UInt32 type)
{
    auto itr = _generators.find(type);
    if (itr != _generators.end() && itr->second) {
        return nullptr;
    }

    auto sptr = std::make_shared<IDGenerator>();
    sptr->SetID(type);
    sptr->DBFieldRegister();

    if (sptr->InsertToDB("glob_id", nullptr)) {
        sptr->SyncDataToDB("glob_id", nullptr);
        _generators[type] = sptr;
        return sptr;
    }
    return nullptr;
}

IDGeneratorSptr IDGeneratorMgr::FindGenerator(UInt32 type)
{
    auto itr = _generators.find(type);
    if (itr != _generators.end()) {
        return itr->second;
    }

    return nullptr;
}
