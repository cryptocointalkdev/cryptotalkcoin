// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2018 The Cryptotalkcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <pow.h>

#include <arith_uint256.h>
#include <chain.h>
#include <primitives/block.h>
#include <uint256.h>

unsigned int CalculateNextWorkRequired(const CBlockIndex* pindexLast, int64_t nFirstBlockTime, const Consensus::Params& params) {
    // current difficulty formula, darkcoin - DarkGravity v3, written by Evan Duffield - evan@darkcoin.io 
    const CBlockIndex *BlockLastSolved = pindexLast;
    const CBlockIndex *BlockReading = pindexLast;
    int64_t nActualTimespan = 0;
    int64_t LastBlockTime = 0;
    int64_t PastBlocksMin = 6;
    int64_t PastBlocksMax = 6;
    int64_t CountBlocks = 0;
    arith_uint256 PastDifficultyAverage;
    arith_uint256 PastDifficultyAveragePrev;
    
    if (BlockLastSolved == NULL || BlockLastSolved->nHeight == 0 || BlockLastSolved->nHeight < PastBlocksMin) {
		return UintToArith256(params.powLimit).GetCompact();
    }
    
    for (unsigned int i = 1; BlockReading && BlockReading->nHeight > 0; i++) {
        if (PastBlocksMax > 0 && i > PastBlocksMax) { break; }
        CountBlocks++;

        if(CountBlocks <= PastBlocksMin) {
            if (CountBlocks == 1) { 
				PastDifficultyAverage.SetCompact(BlockReading->nBits); 
			}
            else { 
				PastDifficultyAverage = ((PastDifficultyAveragePrev * CountBlocks)+(PastDifficultyAverage.SetCompact(BlockReading->nBits))) / (CountBlocks+1); 
			}
            PastDifficultyAveragePrev = PastDifficultyAverage;
        }

        if(LastBlockTime > 0){
            int64_t Diff = (LastBlockTime - BlockReading->GetBlockTime());
            nActualTimespan += Diff;
        }
        LastBlockTime = BlockReading->GetBlockTime();

        if (BlockReading->pprev == NULL) { assert(BlockReading); break; }
        BlockReading = BlockReading->pprev;
    }
    const arith_uint256 bnPowLimit = UintToArith256(params.powLimit);

    arith_uint256 bnNew = PastDifficultyAverage;

    int64_t nTargetTimespan = CountBlocks*params.nPowTargetSpacing;

    if (nActualTimespan < nTargetTimespan/3)
        nActualTimespan = nTargetTimespan/3;
    if (nActualTimespan > nTargetTimespan*3)
        nActualTimespan = nTargetTimespan*3;

    // Retarget
    bnNew *= nActualTimespan;
    bnNew /= nTargetTimespan;

	if (bnNew > bnPowLimit) {
		bnNew = bnPowLimit;
	}
    return bnNew.GetCompact();
}


unsigned int GetNextWorkRequired(const CBlockIndex* pindexLast, const CBlockHeader *pblock, const Consensus::Params& params){
    if (params.fPowAllowMinDifficultyBlocks)  {

		 // Special difficulty rule for testnet:
		 // If the new block's timestamp is more than 2* 10 minutes
		 // then allow mining of a min-difficulty block.

		if (pblock->GetBlockTime() > pindexLast->GetBlockTime() + params.nPowTargetSpacing*2)
			return UintToArith256(params.powLimit).GetCompact();
    }
    return CalculateNextWorkRequired(pindexLast, pindexLast->GetBlockTime(), params);
}
/*

unsigned int GetNextWorkRequired(const CBlockIndex* pindexLast, const CBlockHeader *pblock, const Consensus::Params& params)
{
    assert(pindexLast != nullptr);
    unsigned int nProofOfWorkLimit = UintToArith256(params.powLimit).GetCompact();

    // Only change once per difficulty adjustment interval
    if ((pindexLast->nHeight+1) % params.DifficultyAdjustmentInterval() != 0)
    {
        if (params.fPowAllowMinDifficultyBlocks)
        {
            // Special difficulty rule for testnet:
            // If the new block's timestamp is more than 2* 10 minutes
            // then allow mining of a min-difficulty block.
            if (pblock->GetBlockTime() > pindexLast->GetBlockTime() + params.nPowTargetSpacing*2)
                return nProofOfWorkLimit;
            else
            {
                // Return the last non-special-min-difficulty-rules-block
                const CBlockIndex* pindex = pindexLast;
                while (pindex->pprev && pindex->nHeight % params.DifficultyAdjustmentInterval() != 0 && pindex->nBits == nProofOfWorkLimit)
                    pindex = pindex->pprev;
                return pindex->nBits;
            }
        }
        return pindexLast->nBits;
    }

    // Go back by what we want to be 14 days worth of blocks
    int nHeightFirst = pindexLast->nHeight - (params.DifficultyAdjustmentInterval()-1);
    assert(nHeightFirst >= 0);
    const CBlockIndex* pindexFirst = pindexLast->GetAncestor(nHeightFirst);
    assert(pindexFirst);

    return CalculateNextWorkRequired(pindexLast, pindexFirst->GetBlockTime(), params);
}

unsigned int CalculateNextWorkRequired(const CBlockIndex* pindexLast, int64_t nFirstBlockTime, const Consensus::Params& params)
{
    if (params.fPowNoRetargeting)
        return pindexLast->nBits;

    // Limit adjustment step
    int64_t nActualTimespan = pindexLast->GetBlockTime() - nFirstBlockTime;
    if (nActualTimespan < params.nPowTargetTimespan/4)
        nActualTimespan = params.nPowTargetTimespan/4;
    if (nActualTimespan > params.nPowTargetTimespan*4)
        nActualTimespan = params.nPowTargetTimespan*4;

    // Retarget
    const arith_uint256 bnPowLimit = UintToArith256(params.powLimit);
    arith_uint256 bnNew;
    bnNew.SetCompact(pindexLast->nBits);
    bnNew *= nActualTimespan;
    bnNew /= params.nPowTargetTimespan;

    if (bnNew > bnPowLimit)
        bnNew = bnPowLimit;

    return bnNew.GetCompact();
}
*/
bool CheckProofOfWork(uint256 hash, unsigned int nBits, const Consensus::Params& params)
{
    bool fNegative;
    bool fOverflow;
    arith_uint256 bnTarget;

    bnTarget.SetCompact(nBits, &fNegative, &fOverflow);

    // Check range
    if (fNegative || bnTarget == 0 || fOverflow || bnTarget > UintToArith256(params.powLimit))
        return false;

    // Check proof of work matches claimed amount
    if (UintToArith256(hash) > bnTarget)
        return false;

    return true;
}
