#pragma once

#include <memory>    // unique_ptr
#include <string>
#include <vector>

#include "TechnicalServices/Logging/LoggerHandler.hpp"
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"




namespace TechnicalServices::Persistence
{
  class SimpleDB : public TechnicalServices::Persistence::PersistenceHandler
  {
    public:
      using PersistenceHandler::PersistenceHandler;    // inherit constructors
      SimpleDB();


      // Operations
      std::vector<std::string> findRoles()                                       override;  // Returns list of all legal roles
      AccountCredentials          findCredentialsByName( const std::string & name ) override;  // Returns credentials for specified user, throws NoSuchUser if user not found
      std::vector<AccountCredentials> findReportedUsers(std::string date) override;
      bool removeAccount(std::string accountID) override;
      AccountCredentials findCredentialsByID(const std::string & ID) override;
      std::string findUserReport(const std::string & accountID) override;
      std::string setUsername(std::string accountID, std::string username) override;
      std::string setPassword(std::string accountID, std::string password) override;
      std::vector<JobCredentials> listJobs(std::string company) override;
      std::string getJobListingReport(std::string jobID) override;
      std::string removeJobListing(std::string jobID) override;

      // Adaptation Data read only access.  Adaptation data is a Key/Value pair
      const std::string & operator[]( const std::string & key ) const override;


      ~SimpleDB() noexcept override;

    private:
      std::unique_ptr<TechnicalServices::Logging::LoggerHandler> _loggerPtr;

      // convenience reference object enabling standard insertion syntax
      // This line must be physically after the definition of _loggerPtr
      TechnicalServices::Logging::LoggerHandler & _logger = *_loggerPtr;


      // Property data (Key/Value pairs) off-line modifiable by the end-user
      using AdaptationData = std::map<std::string /*Key*/, std::string /*Value*/>;
      AdaptationData _adaptablePairs;

  }; // class SimpleDB
}  // namespace TechnicalServices::Persistence
