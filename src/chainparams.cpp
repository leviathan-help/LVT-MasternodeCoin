// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2019 The PIVX developers
// Copyright (c) 2019 The LEVIATHAN developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
boost::assign::map_list_of
(0, uint256("0x000004900f99b4fd78e6bca52ac0ed79da851aabe1178a2a7218c5d0f4f723aa"))
(1, uint256("0x0000043589a011b13dddd1e74916af5586c5f1e664dc9586f4df1c8f0f3307a2"))
(742, uint256("0xf46a571bb096c0e75b1bd77e062e46f16de0ae688e58ae0844ba8b75499b5228"))
(2587, uint256("0x8a3457c7aa4f1eef4d7fd981217bf6ecbd1231ea4d0700af14bef6cc96cfae6f"))
(5201, uint256("0xcc0e339496224fd726e4dedc86ef40ee15d673d673c7911f4a876339f9321d5c"))
(8654, uint256("0x62c56f4bca382907c75be48e6d0949c6cb93cad16523d2f4b2b9a1784c70c44a"))
(15732, uint256("0xd3660e44456e5d2ee1ebac3a4c807dc95758eb95fc73c1e10c7455fe948d4c08"))
(20143, uint256("0x773ad6730b2cbd6327f834dad676cb106afb033dd77880d70c63573019bf2437"))
(23576, uint256("0xec3cbd3ce2923e1017d0e7adc59b3180fced671e71b1fd3814df47d7d118d160"))
(28854, uint256("0x81814ff9f8da2a736039395c9df29a65193a99bcfd7740aa6701539e5218523c"))

;
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1565687988, // * UNIX timestamp of last checkpoint block
    58679,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (0, uint256("0x001"))
	;
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1560843157,
    2501682,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1563948000,
    0,
    100};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params() const
{
    assert(this);
    static CBigNum bnDecModulus = 0;
    if (!bnDecModulus)
        bnDecModulus.SetDec(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsDec = libzerocoin::ZerocoinParams(bnDecModulus);

    return &ZCParamsDec;
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x74;
        pchMessageStart[1] = 0xd1;
        pchMessageStart[2] = 0xcb;
        pchMessageStart[3] = 0xa5;
        vAlertPubKey = ParseHex("0000091d3ba6ba6e7423fa5cad6b65e0a9a5348f18d332b44a5cb1a8b7eddc1eaa335fc8dc4f012cb8241cc0bdafd6ca70c5f5448916e4e6f511bcd746ed18da31");
        nDefaultPort = 12110;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // LEVIATHAN starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 8100; // 75%
        nRejectBlockOutdatedMajority = 10260; // 95%
        nToCheckBlockUpgradeMajority = 10800; // Approximate expected amount of blocks in 7 days (1440*7.5)
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // LEVIATHAN: 1 day
        nTargetSpacing = 1 * 60;  // LEVIATHAN: 1 minute
        nMaturity = 61;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 1000000000 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 200;
        nZerocoinStartHeight = 210;
        nZerocoinStartTime = 1563948000; 
        nBlockLastGoodCheckpoint = 210; //Last valid accumulator checkpoint
        nBlockZerocoinV2 = 210; //!> The block that zerocoin v2 becomes active - roughly Tuesday, May 8, 2018 4:00:00 AM GMT
        nBlockDoubleAccumulated = 0;

        // Public coin spend enforcement
        nPublicZCSpends = 300;

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         *
         * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
         *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
         *   vMerkleTree: e0028e
         */
        const char* pszTimestamp = "LVT Masternode Coin";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 250 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04c10e83b2703bc1265f7dbd1bad5855ac7c10bd055814ce121ba32607d573b8810c02c0582aed15b4deb9c4b77b26d92422a4e256cd42774babeaba073b2ed9c1") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 4;
		genesis.nAccumulatorCheckpoint = 0;
        genesis.nTime = 1563948000;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 1732197;

        hashGenesisBlock = genesis.GetHash();

		assert(hashGenesisBlock == uint256("0x000004900f99b4fd78e6bca52ac0ed79da851aabe1178a2a7218c5d0f4f723aa"));
		assert(genesis.hashMerkleRoot == uint256("0x773fb591654cfd6a515f816ea002c76179995acef2bd2f55552c87662c5dd554"));

        vSeeds.push_back(CDNSSeedData("1", "dnsseederlvt.leviathan-coin.com"));    
        vSeeds.push_back(CDNSSeedData("2", "explorer.leviathan-coin.com"));    
		vSeeds.push_back(CDNSSeedData("3", "seed1.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("4", "seed2.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("5", "seed3.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("6", "seed4.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("7", "seed5.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("8", "seed6.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("9", "seed7.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("10", "seed8.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("11", "seed9.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("12", "seed10.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("13", "seed11.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("14", "seed12.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("15", "seed13.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("16", "seed14.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("17", "seed15.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("18", "seed16.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("19", "seed17.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("20", "seed18.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("21", "seed19.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("22", "seed20.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("23", "seed21.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("24", "seed22.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("25", "seed23.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("26", "seed24.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("27", "seed25.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("28", "seed26.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("29", "seed27.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("30", "seed28.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("31", "seed29.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("32", "seed30.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("33", "seed31.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("34", "seed32.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("35", "seed33.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("36", "seed34.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("37", "seed35.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("38", "seed36.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("39", "seed37.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("40", "seed38.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("41", "seed39.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("42", "seed40.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("43", "seed41.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("44", "seed42.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("45", "seed43.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("46", "seed44.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("47", "seed45.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("48", "seed46.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("49", "seed47.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("50", "seed48.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("51", "seed49.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("52", "seed50.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("53", "seed51.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("54", "seed52.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("55", "seed53.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("56", "seed54.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("57", "seed55.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("58", "seed56.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("59", "seed57.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("60", "seed58.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("61", "seed59.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("62", "seed60.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("63", "seed61.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("64", "seed62.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("65", "seed63.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("66", "seed64.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("67", "seed65.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("68", "seed66.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("69", "seed67.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("70", "seed68.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("71", "seed69.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("72", "seed70.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("73", "seed71.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("74", "seed72.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("75", "seed73.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("76", "seed74.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("77", "seed75.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("78", "seed76.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("79", "seed77.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("80", "seed78.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("81", "seed79.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("82", "seed80.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("83", "seed81.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("84", "seed82.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("85", "seed83.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("86", "seed84.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("87", "seed85.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("88", "seed86.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("89", "seed87.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("90", "seed88.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("91", "seed89.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("92", "seed90.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("93", "seed91.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("94", "seed92.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("95", "seed93.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("96", "seed94.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("97", "seed95.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("98", "seed96.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("99", "seed97.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("100", "seed98.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("101", "seed99.leviathan-coin.com"));
		vSeeds.push_back(CDNSSeedData("102", "seed100.leviathan-coin.com")); 

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 48);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 13);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 212);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        nBudgetCycleBlocks = 43200; //!< Amount of blocks in a months period of time (using 1 minutes per) = (60*24*30)
        strSporkKey = "040f9edabcc68a8d7d0a689ccd95c6813f328e3999ea972d489e246b7e5f0859ab0e6ce47702801a35139298f3104345b2035ed73e18ab43777955704897a19d1b";
        strObfuscationPoolDummyAddress = "LcsctEgXt3gCvmnyfDjjVugezrobi7FzhX";

        /** Zerocoin */
        zerocoinModulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
            "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
            "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
            "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
            "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
            "31438167899885040445364023527381951378636564391212010397122822120720357";
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMaxZerocoinPublicSpendsPerTransaction = 637; // Assume about 220 bytes each input
        nMinZerocoinMintFee = 1 * CENT; //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100; //full security level for accumulators
        nZerocoinHeaderVersion = 4; //Block headers must be this version once zerocoin is active
        nZerocoinRequiredStakeDepth = 200; //The required confirmations for a zlvt to be stakable

        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
        nProposalEstablishmentTime = 60 * 60 * 24; // Proposals must be at least a day old to make it into a budget
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x45;
        pchMessageStart[1] = 0x76;
        pchMessageStart[2] = 0x65;
        pchMessageStart[3] = 0xba;
        vAlertPubKey = ParseHex("000010e83b2703ccf322f7dbd62dd5855ac7c10bd055814ce121ba32607d573b8810c02c0582aed05b4deb9c4b77b26d92428c61256cd42774babea0a073b2ed0c9");
        nDefaultPort = 51474;
        nEnforceBlockUpgradeMajority = 4320; // 75%
        nRejectBlockOutdatedMajority = 5472; // 95%
        nToCheckBlockUpgradeMajority = 5760; // 4 days
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // LEVIATHAN: 1 day
        nTargetSpacing = 1 * 60;  // LEVIATHAN: 1 minute
        nLastPOWBlock = 200;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nMaxMoneyOut = 43199500 * COIN;

        // Public coin spend enforcement
        nPublicZCSpends = 1106100;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1563948000;
        genesis.nNonce = 2402015;

        hashGenesisBlock = genesis.GetHash();
        //assert(hashGenesisBlock == uint256("0x0000041e482b9b9691d98eefb48473405c0b8ec31b76df3797c74a78680ef818"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("fuzzbawls.pw", "leviathan-testnet.seed.fuzzbawls.pw"));
        vSeeds.push_back(CDNSSeedData("fuzzbawls.pw", "leviathan-testnet.seed2.fuzzbawls.pw"));
        vSeeds.push_back(CDNSSeedData("warrows.dev", "testnet.dnsseed.leviathan.warrows.dev"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet leviathan addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet leviathan script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet leviathan BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet leviathan BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet leviathan BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        nBudgetCycleBlocks = 144; //!< Ten cycles per day on testnet
        strSporkKey = "04A8B319388C0F8588D238B9941DC26B26D3F9465266B368A051C5C100F79306A557780101FE2192FE170D7E6DEFDCBEE4C8D533396389C0DAFFDBC842B002243C";
        strObfuscationPoolDummyAddress = "y57cqfGRkekRyDRNeJiLtYVEbvhXrNbmox";
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet

        nProposalEstablishmentTime = 60 * 5; // Proposals must be at least 5 mns old to make it into a test budget
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x7e;
        pchMessageStart[3] = 0xac;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // LEVIATHAN: 1 day
        nTargetSpacing = 1 * 60;        // LEVIATHAN: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        nLastPOWBlock = 250;
        nMaturity = 100;
        nMasternodeCountDrift = 4;
        //nModifierUpdateBlock = 0; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 43199500 * COIN;
        nZerocoinStartHeight = 300;
        nBlockZerocoinV2 = 300;
        nZerocoinStartTime = 1501776000;
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 999999999; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 999999999; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 999999999; //Last valid accumulator checkpoint

        // Public coin spend enforcement
        nPublicZCSpends = 350;

        //! Modify the regtest genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1563948000;
        genesis.nNonce = 2402015;

        hashGenesisBlock = genesis.GetHash();
        //assert(hashGenesisBlock == uint256("0x0000041e482b9b9691d98eefb48473405c0b8ec31b76df3797c74a78680ef818"));
        //assert(hashGenesisBlock == uint256("0x4f023a2120d9127b21bbad01724fdb79b519f593f2a85b60d3d79160ec5f29df"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 51478;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
