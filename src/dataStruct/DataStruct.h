#ifndef OCB_DATASTRUCT_H
#define OCB_DATASTRUCT_H

#pragma pack(push)
#pragma pack(1)
struct data
{
    uint64_t claimBlockNumber, stackBlockNumber;
    boost::uuids::uuid claimUUID, stackUUID;
    uint16_t claimUserAmount, stackUserAmount;
    std::vector<uint16_t> paymentID;
    std::vector<byte *> publicKeys, signatures;
    byte *bufferReferenceData = new byte[sizeof(uint64_t) + sizeof(uint16_t) + sizeof(boost::uuids::uuid) +
                                           (sizeof(uint16_t) * (claimUserAmount))];
} parsedData;
#pragma pack(pop)

#endif //OCB_DATASTRUCT_H
