#include "extern_c/handlers/ModioModCreator.h"

extern "C"
{
  void modioInitAddModHandler(ModioModCreator* mod_creator)
  {
    mod_creator->logo = NULL;
    mod_creator->name = NULL;
    mod_creator->name_id = NULL;
    mod_creator->summary = NULL;
    mod_creator->description = NULL;
    mod_creator->homepage = NULL;
    mod_creator->metadata_blob = NULL;
    mod_creator->tags = NULL;
  }

  void modioSetAddModLogoPath(ModioModCreator* mod_creator, char* logo_path)
  {
    if(mod_creator->logo)
      delete[] mod_creator->logo;

    mod_creator->logo = new char[strlen(logo_path) + 1];
    strcpy(mod_creator->logo, logo_path);
  }

  void modioSetAddModName(ModioModCreator* mod_creator, char* name)
  {
    if(mod_creator->name)
      delete[] mod_creator->name;

    mod_creator->name = new char[strlen(name) + 1];
    strcpy(mod_creator->name, name);
  }

  void modioSetAddModNameid(ModioModCreator* mod_creator, char* name_id)
  {
    if(mod_creator->name_id)
    delete[] mod_creator->name_id;

    mod_creator->name_id = new char[strlen(name_id) + 1];
    strcpy(mod_creator->name_id, name_id);
  }

  void modioSetAddModSummary(ModioModCreator* mod_creator, char* summary)
  {
    if(mod_creator->summary)
    delete[] mod_creator->summary;

    mod_creator->summary = new char[strlen(summary) + 1];
    strcpy(mod_creator->summary, summary);
  }

  void modioSetAddModDescription(ModioModCreator* mod_creator, char* description)
  {
    if(mod_creator->description)
    delete[] mod_creator->description;

    mod_creator->description = new char[strlen(description) + 1];
    strcpy(mod_creator->description, description);
  }

  void modioSetAddModHomepage(ModioModCreator* mod_creator, char* homepage)
  {
    if(mod_creator->homepage)
      delete[] mod_creator->homepage;

    mod_creator->homepage = new char[strlen(homepage) + 1];
    strcpy(mod_creator->homepage, homepage);
  }

  void modioSetAddModMetadataBlob(ModioModCreator* mod_creator, char* metadata_blob)
  {
    if(mod_creator->metadata_blob)
      delete[] mod_creator->metadata_blob;

    mod_creator->metadata_blob = new char[strlen(metadata_blob) + 1];
    strcpy(mod_creator->metadata_blob, metadata_blob);
  }

  void modioAddTagAddMod(ModioModCreator* mod_creator, char* tag)
  {
    ModioListNode* new_tag = new ModioListNode;
    modioInitNode(new_tag);
    new_tag->value = new char[strlen(tag) + 1];
    strcpy(new_tag->value, tag);

    if(!mod_creator->tags)
    {
      mod_creator->tags = new_tag;
    }else
    {
      ModioListNode* last_tag = mod_creator->tags;
      while(last_tag->next)
      {
        last_tag = last_tag->next;
      }
      last_tag->next = new_tag;
    }
  }

  void modioFreeAddModHandler(ModioModCreator* mod_creator)
  {
    delete mod_creator->logo;
    delete mod_creator->name;
    delete mod_creator->homepage;
    delete mod_creator->summary;
    delete mod_creator->description;
    delete mod_creator->metadata_blob;
    delete mod_creator->name_id;
    delete mod_creator->tags;
  }
}

namespace modio
{
  std::map<std::string, std::string> getModfileCurlFormFilesParams(ModioModCreator* mod_creator)
  {
    std::map<std::string, std::string> result;

    if(mod_creator->logo)
      result.insert(std::pair<std::string,std::string>("logo",mod_creator->logo));

    return result;
  }

  std::multimap<std::string, std::string> getAddModfileCurlFormCopyContentsParams(ModioModCreator* mod_creator)
  {
    std::multimap<std::string, std::string> result;

    if(mod_creator->name)
      result.insert(std::pair<std::string,std::string>("name",mod_creator->name));

    if(mod_creator->name_id)
      result.insert(std::pair<std::string,std::string>("name_id",mod_creator->name_id));

    if(mod_creator->summary)
      result.insert(std::pair<std::string,std::string>("summary",mod_creator->summary));

    if(mod_creator->description)
      result.insert(std::pair<std::string,std::string>("description",mod_creator->description));

    if(mod_creator->homepage)
      result.insert(std::pair<std::string,std::string>("homepage",mod_creator->homepage));

    if(mod_creator->metadata_blob)
      result.insert(std::pair<std::string,std::string>("metadata_blob",mod_creator->metadata_blob));

    if(mod_creator->tags)
    {
      ModioListNode* current_tag = mod_creator->tags;
      while(current_tag)
      {
        result.insert(std::pair<std::string,std::string>("tags[]",current_tag->value));
        current_tag = current_tag->next;
      }
    }

    return result;
  }
}
