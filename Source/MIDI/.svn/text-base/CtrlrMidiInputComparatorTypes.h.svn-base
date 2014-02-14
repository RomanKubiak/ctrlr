#ifndef __CTRLR_MIDI_INPUT_COMPARATOR_TYPES_H__
#define __CTRLR_MIDI_INPUT_COMPARATOR_TYPES_H__

class CtrlrMapData
{
	public:
		CtrlrMapData (CtrlrModulator *_target)
		{
			targets.add (_target);
		}

		CtrlrMapData (const CtrlrMapData &other)
		{
			targets = other.targets;
		}

		CtrlrMapData(){}

		~CtrlrMapData()
		{
			targets.clear();
		}

		Array<CtrlrModulator*> targets;

		JUCE_LEAK_DETECTOR(CtrlrMapData);
};

class CtrlrCacheDataMulti
{
	public:
		CtrlrCacheDataMulti(const BigInteger &_key, const CtrlrMapData &_mapData) : mapData(_mapData), key(_key)
		{
		}

		CtrlrCacheDataMulti()
		{
		}

		bool operator== (const CtrlrCacheDataMulti& other) const noexcept
		{
			if (key == other.key)
				return (true);

			return (false);
		}

		CtrlrMapData mapData;
		BigInteger key;

		JUCE_LEAK_DETECTOR(CtrlrCacheDataMulti);
};

class CtrlrCacheDataSingle
{
	public:
		CtrlrCacheDataSingle(const int &_key, const CtrlrMapData &_mapData) : mapData(_mapData), key(_key)
		{
		}

		CtrlrCacheDataSingle()
		{
		}

		bool operator== (const CtrlrCacheDataSingle& other) const noexcept
		{
			if (key == other.key)
				return (true);

			return (false);
		}

		CtrlrMapData mapData;
		int key;

		JUCE_LEAK_DETECTOR(CtrlrCacheDataSingle);
};

typedef std::map<BigInteger,CtrlrMapData>					CtrlrMultiMidiMap;
typedef std::pair<BigInteger,CtrlrMapData>					CtrlrMultiMidiMapPair;
typedef std::map<BigInteger,CtrlrMapData>::iterator			CtrlrMultiMidiMapIterator;
typedef std::map<BigInteger,CtrlrMapData>::reverse_iterator	CtrlrMultiMidiMapRIterator;
typedef std::map<int,CtrlrMapData>							CtrlrMidiMap;
typedef std::map<int,CtrlrMapData>::iterator				CtrlrMidiMapIterator;
typedef std::pair<int,CtrlrMapData>							CtrlrMidiMapPair;
#endif
