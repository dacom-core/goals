
#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/time.hpp>
#include <eosiolib/currency.hpp>
#include <eosiolib/multi_index.hpp>
#include <eosiolib/contract.hpp>
//#include "eosio.token.hpp"

#define LEPTS_PRECISION 1000000
#define PERCENT_PRECISION 10000


namespace eosio {
    static const account_name _self = N(goals);
    static const eosio::symbol_name _SYM = S(4, FLO);
    static const account_name _protocol = N(tt.tc);


    struct spiral{
        uint64_t id;
        uint64_t size_of_pool;
        uint64_t overlap;
        uint64_t profit_growth;
        uint64_t base_rate;
        uint64_t loss_percent;
        uint64_t pool_limit;
        uint64_t pool_timeout;
        uint64_t priority_seconds;
        uint64_t primary_key() const {return id;}

        EOSLIB_SERIALIZE(spiral, (id)(size_of_pool)(overlap)(profit_growth)(base_rate)(loss_percent)(pool_limit)(pool_timeout)(priority_seconds))
    };

    typedef eosio::multi_index<N(spiral), spiral> spiral_index;

    struct rate {
        uint64_t pool_id;
        uint64_t total_lepts;
        uint64_t buy_rate=0;
        uint64_t sell_rate=0;
        eosio::asset client_income;
        eosio::asset delta;
        eosio::asset pool_cost;
        eosio::asset total_in_box;
        eosio::asset payment_to_wins;
        eosio::asset payment_to_loss;
        eosio::asset system_income;
        eosio::asset live_balance_for_sale;
        
        
        uint64_t primary_key() const{return pool_id;}

        EOSLIB_SERIALIZE(rate, (pool_id)(total_lepts)(buy_rate)(sell_rate)(client_income)(delta)(pool_cost)(total_in_box)(payment_to_wins)(payment_to_loss)(system_income)(live_balance_for_sale))
    };
    typedef eosio::multi_index<N(rate), rate> rate_index;
    

    // @abi table goals
    struct goals{
        uint64_t id;
        account_name username;
        bool activated = false;
        bool completed = false;
        account_name host;
        std::string shortdescr;
        std::string descr;
        eosio::asset cost;
        eosio::asset nominal;
        eosio::asset collected;
        bool reported = false;
        std::string report;
        bool validated = false;
        
        uint64_t primary_key()const { return id; }
        
        EOSLIB_SERIALIZE( goals, (id)(username)(activated)(completed)(host)(shortdescr)(descr)(cost)(nominal)(collected)(reported)(report)(validated))
    };

    typedef eosio::multi_index <N(goals), goals> goals_index;
    //by activated //by username

    // @abi table chain i64
    struct chain{
        uint64_t id;
        account_name username;
        uint64_t goal_id;
        bool in_protocol = false;
        uint64_t primary_key() const {return id;}

        EOSLIB_SERIALIZE(chain, (id)(username)(goal_id)(in_protocol))
    };

    typedef eosio::multi_index<N(chain), chain> chain_index;


    /* ACTIONS */

    // @abi action
    struct setgoal{
        account_name username;
        account_name host;
        std::string shortdescr;
        std::string descr;
        eosio::asset cost;

        EOSLIB_SERIALIZE( setgoal, (username)(host)(shortdescr)(descr)(cost))
    };

      // @abi action
    struct editgoal{
        account_name username;
        account_name host;
        uint64_t goal_id;
        std::string shortdescr;
        std::string descr;
        eosio::asset cost;

        EOSLIB_SERIALIZE( editgoal, (username)(host)(goal_id)(shortdescr)(descr)(cost))

    };

    // @abi action
    struct delgoal{
        account_name username;
        uint64_t goal_id;
        EOSLIB_SERIALIZE( delgoal, (username)(goal_id))
    };

    // @abi action
    struct report{
        account_name username;
        uint64_t goal_id;
        std::string report;
        EOSLIB_SERIALIZE( struct report, (username)(goal_id)(report))
    };

    // @abi action
    struct withdraw{
        account_name username;
        uint64_t goal_id;
        EOSLIB_SERIALIZE( withdraw, (username)(goal_id))
    };    
};






