#pragma once
#include "bellshire/matml31.hxx"
#include "bellshire/matml31_strongly_typed_def.h"
#include <type_traits>
#include <vector>
#include "bellshire/utilities/BT_MatML_has_a_idref.h"

//List all the members that are a idref.
namespace bellshire::utilities
{
	class Get_IdRefPtrs
	{
	public:
		using value_type = std::vector<xml_schema::idref*>;

		value_type value{};

		template<class MatML>
		Get_IdRefPtrs(observer_ptr<MatML> element)
		{
				if constexpr (has_authority_type<MatML>::value) Get_Authority(element);
				if constexpr (has_parameter_type<MatML>::value) Get_Parameter(element);
				if constexpr (has_property_type<MatML>::value) Get_Property(element);
				if constexpr (has_technique_type<MatML>::value) Get_Technique(element);
				if constexpr (has_source_type<MatML>::value) Get_Source(element);
				if constexpr (has_specimen_type<MatML>::value) Get_Specimen(element);
				if constexpr (has_test_type<MatML>::value) Get_Test(element);
				//if constexpr (has_id_type<MatML>::value) Get_Id(element);
		}

		//authority
		template< class MatML, typename std::enable_if<
			!has_authority_type<MatML>::value,
			int >::type = 0 >
		void Get_Authority(const observer_ptr<MatML> element) {}

		template<class MatML, typename std::enable_if<
			(has_authority_type<MatML>::value && !has_authority_optional<MatML>::value),
			int>::type = 0 >
		void Get_Authority
			(const observer_ptr<MatML> element )
		{
			if (element) {
				value.emplace_back(&element->authority());
			}
		}

		template<class MatML, typename std::enable_if<
			(has_authority_type<MatML>::value && has_authority_optional<MatML>::value),
			int>::type = 0 >
		void Get_Authority
			(const observer_ptr<MatML> element )
		{
			if (element) {
				if (element->authority().present()) (value.emplace_back(&element->authority().get()));
			}
		}

		//parameter
		template<class MatML, typename std::enable_if<
			!has_parameter_type<MatML>::value,
			int>::type = 0 >
		void Get_Parameter(const observer_ptr<MatML> element) {}

		template<class MatML, typename std::enable_if<
			has_parameter_type<MatML>::value,
			int>::type = 0  >
		void Get_Parameter(const observer_ptr<MatML> element)
		{
			if (element) {
				value.emplace_back(&element->parameter());
			}
		}

		//property
		template<class MatML, typename std::enable_if<
			!has_property_type<MatML>::value,
			int>::type = 0  >
		void Get_Property(const observer_ptr<MatML> element) {}

		template<class MatML, typename std::enable_if<
			has_property_type<MatML>::value,
			int>::type = 0   >
		void Get_Property(const observer_ptr<MatML> element)
		{
			if (element) {
				value.emplace_back(&element->property());
			}
		}

		//technique
		template<class MatML, typename std::enable_if<
			!has_technique_type<MatML>::value, 
			int>::type = 0  >
		void Get_Technique(const observer_ptr<MatML> element) {}

		template<class MatML, typename std::enable_if<
			(has_technique_type<MatML>::value && !has_technique_optional<MatML>::value ),
			int>::type = 0  >
		void Get_Technique(const observer_ptr<MatML> element)
		{
			if (element) {
				value.emplace_back(&element->technique());
			}
		}

		template<class MatML, typename std::enable_if<
			(has_technique_type<MatML>::value && has_technique_optional<MatML>::value ),
			int>::type = 0  >
		void Get_Technique(const observer_ptr<MatML> element)
		{
			if (element) {
				if (element->technique().present()) value.emplace_back(&element->technique().get());
			}
		}

		//source
		template<class MatML, typename std::enable_if<
			!has_source_type<MatML>::value,
			int>::type = 0>
		void Get_Source(const observer_ptr<MatML> element) {}

		template<class MatML, typename std::enable_if<
			(has_source_type<MatML>::value && !has_source_optional<MatML>::value), 
			int>::type = 0 >
		void Get_Source(const observer_ptr<MatML> element)
		{
			if (element) {
				value.emplace_back(&element->source());
			}
		}

		template<class MatML, typename std::enable_if<
			(has_source_type<MatML>::value && has_source_optional<MatML>::value), 
			int>::type = 0 >
		void Get_Source(const observer_ptr<MatML> element)
		{
			if (element) {
				if (element->source().present()) value.emplace_back(&element->source().get());
			}
		}

		//specimen
		template<class MatML, typename std::enable_if<
			!has_specimen_type<MatML>::value,
			int>::type = 0>
		void Get_Specimen(const observer_ptr<MatML> element) {}

		template<class MatML, typename std::enable_if<
			(has_specimen_type<MatML>::value && !has_specimen_optional<MatML>::value),
			int>::type = 0>
		void Get_Specimen(const observer_ptr<MatML> element)
		{
			if (element) {
				value.emplace_back(&element->specimen());
			}
		}

		template<class MatML, typename std::enable_if<
			(has_specimen_type<MatML>::value && has_specimen_optional<MatML>::value),
			int>::type = 0>
		void Get_Specimen(const observer_ptr<MatML> element)
		{
			if (element) {
				if (element->specimen().present()) value.emplace_back(&element->specimen().get());
			}
		}

		//test
		template<class MatML, typename std::enable_if<
			!has_test_type<MatML>::value, 
			int>::type = 0>
		void Get_Test(const observer_ptr<MatML> element) {};

		template<class MatML, typename std::enable_if<
			(has_test_type<MatML>::value && !has_test_optional<MatML>::value),
			int>::type = 0 >
		void Get_Test(const observer_ptr<MatML> element)
		{
			if (element) {
				value.emplace_back(&element->test());
			}
		}

		template<class MatML, typename std::enable_if<
			(has_test_type<MatML>::value && has_test_optional<MatML>::value),
			int>::type = 0 >
		void Get_Test(const observer_ptr<MatML> element)
		{
			if (element) {

				if (element->test().present()) value.emplace_back(&element->test().get());
			}
		}

		//id
		//template<class MatML, typename std::enable_if<!has_id_type<MatML>::value, int>::type = 0>
		//void Get_Id(const observer_ptr<MatML> element) {};

		//template<class MatML, typename std::enable_if<has_id_type<MatML>::value, int>::type = 0 >
		//void Get_Id(const observer_ptr<MatML> element)
		//{
		//	return value.emplace_back(&element->id().get());
		//}
	};

};//namespace bellshire

#include "bellshire/utilities/BT_MatML_Get_IdRefPtrs.inl"
