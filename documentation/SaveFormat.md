# 1 Saving map tiles
<ID> : <TileType>
{
    1 : Tile Exists
}
Example - 5x5 map:
    [
        1 1 1 1 1
        1 1 1 1 1
        1 1 1 1 1
        1 1 1 1 1
        1 1 1 1 1
    ]

# 2 Saving Characters
Makers: <MarkerName[*args]: Type> : <Explenation>

{
    "CHARACTER"              : Begin Character save chunk.
    name                     : Character name. [string]
    x,y                      : Coordinates. [int]x2
    alive: Bool              : Character life status.
    atk, def, pow, knwl      : Primary Skills [uint]x5
    lvl, exp, mm, cm, movpts : Miscellaneous values [uint]x5
    mor, lck                 : Miscellaneous values [int]x2
    SS1,E1,SS2,E2,SS3,E3 ... : Secondary Skills, where SS1,2,3... are SecondarySkillTypes [enum]
                                    and empty slots should be marked as -1, expected size is 8.
                                    E1,2,3... are SecondarySkillsLevels [enum], if not SS then also -1
    A1, A2, A2...            : Equipped Artifacts, where A1,2,3,.. are ArtifactTypes [enum]
                                    and empty slots should be marked as -1, expected size is 14.
    WM1, WM2, WM3, WM4       : War machines, where WM1,2,3,4 are WarMachineTypes [enum]
                                    and empty slots should be marked as -1, expected size is 4.
    S1,L1,S2,L2,S3,L3...    : Spells known inside a SpellBook, S1,2,3... are SpellTypes [enum]
                                    L1,2,3,... are Spell levels [uint32_t]
                                    and empty slots should not be marked, there is no expected size,
                                    Mark as -2 if no SpellBook is present
    A1, A2, A3, ...          : Artifact Backpack, where A1,2,3,... are ArtefactTypes [enum]
                                    and empty slots should not be marked, there is no expected size,
                                    Mark as -2 if Backpack is empty.
    F1,U1,M1,L1,S1,CH1,
    F2,U2,M2,L2,S2,CH2,
    F3,U3,M3,L3,S3,CH3,
    ... (all as one line)    : Party, where F1,2,3,.. are FactionTypes [int:enum]
                                U1,2,3,... are UnitTypes [int:enum]
                                M1,2,3,... are UnitStack's morales [short]
                                L1,2,3,... are UnitStack's lucks [short]
                                S1,2,3,... are UnitStack's sizes [short]
                                CH1,2,3,... are UnitStack's current healths, [short]
                                If no unit stack is present in a slot, all F1,U1,M1,L1,S1,CH1 should be marked as -1 respectively.
                                Expected size is 7.
}