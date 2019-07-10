// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <crosschain/interblockchain.h>
#include <protocol.h>
#include <chainparams.h>
#include <util/strencodings.h>

#include <boost/foreach.hpp>

void CIbtp::LoadMsgStart()
{
    vChains.push_back(SChain("Litecoin", "LTC", 0xfb, 0xc0, 0xb6, 0xdb));
    vChains.push_back(SChain("Bitcoin", "BTC", 0xf9, 0xbe, 0xb4, 0xd9));
    vChains.push_back(SChain("Dash", "DSH", 0xbf, 0x0c, 0x6b, 0xbd));
    vChains.push_back(SChain("Codex", "CDX", 0xaa, 0xab, 0xac, 0xad));
}

bool CIbtp::IsIbtpChain(const unsigned char msgStart[], std::string& chainName)
{
    bool bFound = false;
    BOOST_FOREACH(SChain p, vChains)
    {
        unsigned char pchMsg[4] = { p.pchMessageOne, p.pchMessageTwo, p.pchMessageThree, p.pchMessageFour };
        if(memcmp(msgStart, pchMsg, sizeof(pchMsg)) == 0)
        {
            bFound = true;
            chainName = p.sChainName;
            LogPrintf("Found Supported chain: %s\n", p.sChainName.c_str());
        }
    }
    return bFound;
}
 //need to specify addresses for burn
 //need to specify either floating or fixed exchange rates 
 // need to specify limit on the amounts that can be transferred
 // need to specify time-frame, ie blocks when it can be done for each coin 
