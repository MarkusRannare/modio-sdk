#include "instance/ModIOInstance.h"

namespace modio
{
  struct GetModsCall
  {
    const std::function<void(const modio::Response&, std::vector<modio::Mod>& mods)> callback;
  };

  struct AddModCall
  {
    const std::function<void(const modio::Response& response, const modio::Mod& mod)> callback;
  };

  struct EditModCall
  {
    const std::function<void(const modio::Response& response, const modio::Mod& mod)> callback;
  };

  struct DeleteModCall
  {
    const std::function<void(const modio::Response& response, u32 mod_id)> callback;
  };

  std::map<u32, GetModsCall*> get_mods_calls;
  std::map<u32, AddModCall*> add_mod_calls;
  std::map<u32, EditModCall*> edit_mod_calls;
  std::map<u32, DeleteModCall*> delete_mod_calls;

  void onGetMods(void* object, ModioResponse modio_response, ModioMod mods[], u32 mods_size)
  {
    u32 call_id = *((u32*)object);

    modio::Response response;
    response.initialize(modio_response);

    std::vector<modio::Mod> mods_vector;
    mods_vector.resize(mods_size);
    for(u32 i=0; i < mods_size; i++)
    {
      mods_vector[i].initialize(mods[i]);
    }

    get_mods_calls[call_id]->callback((const Response&)response, mods_vector);

    delete (u32*)object;
    delete get_mods_calls[call_id];
    get_mods_calls.erase(call_id);
  }

  void onAddMod(void* object, ModioResponse modio_response, ModioMod mod)
  {
    u32 call_id = *((u32*)object);

    modio::Response response;
    response.initialize(modio_response);

    modio::Mod modio_mod;
    add_mod_calls[call_id]->callback((const Response&)response, modio_mod);

    delete (u32*)object;
    delete add_mod_calls[call_id];
    add_mod_calls.erase(call_id);
  }

  void onEditMod(void* object, ModioResponse modio_response, ModioMod mod)
  {
    u32 call_id = *((u32*)object);

    modio::Response response;
    response.initialize(modio_response);

    modio::Mod modio_mod;
    edit_mod_calls[call_id]->callback((const Response&)response, modio_mod);

    delete (u32*)object;
    delete edit_mod_calls[call_id];
    edit_mod_calls.erase(call_id);
  }

  void onDeleteMod(void* object, ModioResponse modio_response, u32 mod_id)
  {
    u32 call_id = *((u32*)object);

    modio::Response response;
    response.initialize(modio_response);

    delete_mod_calls[call_id]->callback((const modio::Response&)response, mod_id);

    delete (u32*)object;
    delete delete_mod_calls[call_id];
    delete_mod_calls.erase(call_id);
  }

  void Instance::getMods(modio::FilterHandler& filter, const std::function<void(const modio::Response&, const std::vector<modio::Mod> & mods)>& callback)
  {
    const struct GetModsCall* get_mods_call = new GetModsCall{callback};
    get_mods_calls[this->current_call_id] = (GetModsCall*)get_mods_call;

    modioGetMods((void*)new u32(this->current_call_id), *filter.getFilter(), &onGetMods);

    this->current_call_id++;
  }

  void Instance::addMod(modio::ModCreator& mod_handler, const std::function<void(const modio::Response& response, const modio::Mod& mod)>& callback)
  {
    const struct AddModCall* add_mod_call = new AddModCall{callback};
    add_mod_calls[this->current_call_id] = (AddModCall*)add_mod_call;

    modioAddMod((void*)new u32(this->current_call_id), *mod_handler.getModioModCreator(), &onAddMod);

    this->current_call_id++;
  }

  void Instance::editMod(u32 mod_id, modio::ModUpdater& mod_handler, const std::function<void(const modio::Response& response, const modio::Mod& mod)>& callback)
  {
    const struct EditModCall* edit_mod_call = new EditModCall{callback};
    edit_mod_calls[this->current_call_id] = (EditModCall*)edit_mod_call;

    modioEditMod((void*)new u32(this->current_call_id), mod_id, *mod_handler.getModioModUpdater(), &onEditMod);

    this->current_call_id++;
  }

  void Instance::deleteMod(u32 mod_id, const std::function<void(const modio::Response& response, u32 mod_id)>& callback)
  {
    const struct DeleteModCall* delete_mod_call = new DeleteModCall{callback};
    delete_mod_calls[this->current_call_id] = (DeleteModCall*)delete_mod_call;

    modioDeleteMod((void*)new u32(this->current_call_id), mod_id, &onDeleteMod);

    this->current_call_id++;
  }
}
