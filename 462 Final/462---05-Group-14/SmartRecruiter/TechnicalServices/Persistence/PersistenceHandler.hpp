#pragma once

#include <map>
#include <stdexcept>    // domain_error, runtime_error
#include <string>
#include <vector>

namespace TechnicalServices::Persistence
{
  // Function argument type definitions
  struct AccountCredentials
  {
    std::string               userName;
    std::string               passPhrase;
    std::vector<std::string>  roles;
    std::string               accountID;
  };

  struct UserReport
  {
    std::string account_ID;
    std::string report;

   };

   struct JobCredentials
  {
  std::string               employer;
  std::string               position;
  std::string               jobID;
  std::string               status;

  };


  // Persistence Package within the Technical Services Layer Abstract class
  // Singleton Class - only one instance of the DB exists for the entire system
  class PersistenceHandler
  {
    public:
      // Exceptions
      struct PersistenceException : std::runtime_error   {using runtime_error       ::runtime_error;};
      struct   NoSuchUser         : PersistenceException {using PersistenceException::PersistenceException;};
      struct   NoSuchProperty     : PersistenceException {using PersistenceException::PersistenceException;};

      // Creation (Singleton)
      PersistenceHandler            (                            ) = default;
      PersistenceHandler            ( const PersistenceHandler & ) = delete;
      PersistenceHandler & operator=( const PersistenceHandler & ) = delete;
      static  PersistenceHandler & instance();


      // Operations
      virtual std::vector<std::string> findRoles()                                       = 0;   // Returns list of all legal roles
      virtual AccountCredentials          findCredentialsByName( const std::string & name ) = 0;   // Returns credentials for specified user, throws NoSuchUser if user not found
      virtual std::vector<AccountCredentials> findReportedUsers(std::string date) = 0;
      virtual bool removeAccount(std::string accountID) = 0;
      virtual AccountCredentials findCredentialsByID(const std::string & accountID) = 0;
      virtual std::string findUserReport(const std::string & accountID) = 0;
      virtual std::string setUsername(std::string accountID, std::string username) = 0;
      virtual std::string setPassword(std::string accountID, std::string password)  = 0;
      virtual std::vector<JobCredentials> listJobs(std::string company) = 0;
      virtual std::string getJobListingReport(std::string jobID) = 0;
      virtual std::string removeJobListing(std::string jobID) = 0;

      // Adaptation Data read only access.  Adaptation data is a Key/Value pair
      // Throws NoSuchProperty
      virtual const std::string & operator[]( const std::string & key ) const = 0;


      // Destructor
      // Pure virtual destructor helps force the class to be abstract, but must still be implemented
      virtual ~PersistenceHandler() noexcept = 0;
  };

} // namespace TechnicalServices::Persistence
