#pragma once

#include <algorithm>

#include "bellshire/matml31.hxx"
#include "bellshire/matml31_strongly_typed_def.h"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
   template<class Parent,
        class Child,
        class Child_cont,
        class Child_MatML_Base,
        class func_class
    >
   void MatML_Base::SetUpChild(
        observer_ptr<Parent> element,
        Child_cont& (Parent::* cont_func)(),
        func_class& func,
        RecursiveFlags recursive
   )
    {
       
       if (element) {
           observer_ptr<Child_cont> matml_element = &((*element).*cont_func)();

           Child_MatML_Base::TraverseMatMLTree(matml_element, func, recursive);
       }
    }

    template<class Parent,
        class Child,
        class Child_cont,
        class Child_MatML_Base,
        class func_class
    >
    void MatML_Base::SetUpChildOptional(
        observer_ptr<Parent> element,
        Child_cont& (Parent::* cont_func)(),
        func_class& func,
        RecursiveFlags recursive
    )
    {
        auto element_observer{ remove_strongly_typed_on_observer_ptr_v(element) };
        if (element_observer) {

            //const auto& cont {&(element_observer.get()->*cont_func)() };
            const auto* cont{ &((*element_observer).*cont_func)() };

            if (cont->present()) { 
                auto child{ observer_ptr<Child>(&cont->get()) };
                Child_MatML_Base::TraverseMatMLTree(child, func, recursive);
            }
        }
    }

    template<class Parent,
        class Child,
        class Child_cont,
        class Child_MatML_Base,
        class func_class
    >
    void MatML_Base::SetUpChildSequence(observer_ptr<Parent> element,
        Child_cont& (Parent::* cont_func)(),
        func_class& func,
        RecursiveFlags recursive
    )
    {
        if (element) {
            Child_cont& cont((element->*cont_func)());

            if (!cont.empty())
                for (typename Child_cont::iterator itr{ cont.begin() };
                    itr != cont.end();
                    ++itr
                    ) {
                     auto element_child{ remove_strongly_typed_on_observer_ptr_v( &*itr) };
                    Child_MatML_Base::TraverseMatMLTree(element_child, func, recursive);
                }
        }
    }

    /// <summary>
/// Does Nothing. 
/// Child are REQUIRED in the MatML structure and are
/// inserted automatically through the Default classes.
/// </summary>
/// <typeparam name="MatML_Class"></typeparam>
/// <typeparam name="MatML_ContClass"></typeparam>
/// <param name="MatML"></param>
    template<typename MatML_ContClass >
    void  MatML_Base::DeleteChild(MatML_ContClass& MatML)
    {
        //Warning("Can not delete required element");
    }

    template<typename MatML_ContClass >
    void  MatML_Base::DeleteContChild(MatML_ContClass& MatML_Cont)
    {
        auto& cont(MatML_Cont);
        if (cont.present())
            cont.reset();
    }


        template<typename MatML_Class, typename MatML_ContClass>
        void MatML_Base::DeleteSeqContChild(observer_ptr < MatML_Class > matml, MatML_ContClass& matml_cont)
        {
            auto& cont(matml_cont);
            if (matml) {
                //auto is_equal = [matml_shared](MatML_Class matml) {return (void*)&matml == (void*)matml_shared.get(); };
              
                auto is_equal = [matml](auto element) {
                    auto rhs{ remove_strongly_typed_on_observer_ptr_v(matml)};
                    auto lhs{ &element };
                    return lhs == rhs; 
                    };

                auto iter = std::find_if(cont.begin(), cont.end(), is_equal);
                if (iter != cont.end())
                    cont.erase(iter);
            }
        }


        /// <summary>
         /// Does Nothing. 
         /// Child are required in the MatML structure and are
         /// inserted automatically through the Default classes.
         /// </summary>
        template<typename MatML_Class, typename MatML_ContClass>
        void  MatML_Base::PasteChild(observer_ptr < MatML_Class > MatML, MatML_ContClass& MatML_Cont)
        {
            //Warning("Can not paste over Required element");
        }

        template<typename MatML_Class, typename MatML_ContClass>
        void  MatML_Base::PasteContChild(observer_ptr < MatML_Class > matml, MatML_ContClass& matml_cont)
        {
            auto& cont(matml_cont);

            auto matml_observer{ remove_strongly_typed_on_observer_ptr_v(matml) };
            if (matml_observer) {
                if (cont.present())
                    cont = *matml_observer;
                else {
                    cont.set(*matml_observer);
                }
            }
        }

        template<typename MatML_Class, typename MatML_ContClass>
        void  MatML_Base::PasteSeqContChild(observer_ptr < MatML_Class > matml, MatML_ContClass& matml_cont)
        {
            auto& cont(matml_cont);
            if (matml) {
                try {
                    cont.push_back(*matml);
                }
                catch (const xml_schema::duplicate_id&) {}
            }
        }


        /// <summary>
        /// Does Nothing. 
        /// Child are required in the MatML structure and are
        /// inserted automatically through the Default classes.
        /// </summary>
        /// <typeparam name="MatML_Class"></typeparam>
        /// <typeparam name="MatML_ContClass"></typeparam>
        /// <param name="MatML"></param>
        template<typename MatML_Class, typename MatML_ContClass >
        void  MatML_Base::InsertChild(MatML_ContClass& MatML_Cont) {
            //Warning("Required element already exist");
        }

        /// <summary>
        /// Inserts the MatML Data into the MatML container element
        /// </summary>
        /// <typeparam name="MatML_Class"></typeparam>
        /// <typeparam name="MatML_ContClass"></typeparam>
        /// <param name="MatML">MatML Container Class</param>
        template<typename MatML_Class, typename MatML_ContClass >
        void MatML_Base::InsertContChild(MatML_ContClass& MatML_Cont)
        {
            auto& cont(MatML_Cont);
            if (cont.present())
                cont = Default<MatML_Class>();
            else {
                cont.set(Default<MatML_Class>());
            }
        }

        /// <summary>
        /// Inserts the MatML Data into the MatML sequence container element
        /// </summary>
        /// <typeparam name="MatML_Class"></typeparam>
        /// <typeparam name="MatML_ContClass"></typeparam>
        /// <param name="MatML"></param>
        template<typename MatML_Class, typename MatML_ContClass >
        void  MatML_Base::InsertSeqContChild(MatML_ContClass& MatML_Cont)
        {
            auto& cont(MatML_Cont);
            try {
                cont.push_back(Default<MatML_Class>());
            }
            catch (const xml_schema::duplicate_id&) {}
        }

        template<class MatML_Class>
        void MatML_Base::Swap(observer_ptr < MatML_Class >& matml0, observer_ptr < MatML_Class >& matml1)
        {
            assert(matml0 && matml1);

            auto temp0(*matml0);
            auto temp1(*matml1);

            *matml0 = temp1;
            *matml1 = temp0;
        }

        /// <summary>
        /// Swap function with MatML Classes that have required Id.
        /// This has the added complication that the id's can not
        /// be duplicated during the swap.
        /// </summary>
        /// <typeparam name="MatML_Class"></typeparam>
        /// <param name="matml0"></param>
        /// <param name="matml1"></param>
        template<class MatML_Class>
        void MatML_Base::SwapHavingId(observer_ptr < MatML_Class >&matml0, observer_ptr < MatML_Class >& matml1)
        {

            assert(matml0 && matml1);
            
                auto temp0(*matml0);
                auto temp1(*matml1);

                //Replace the id to prevent id collision
                auto tempid(temp1.id());
                temp1.id(xml_schema::id(std::string("BT-TEMP-ID")));

                *matml0 = temp1;
                *matml1 = temp0;

                //Replace the temp id with the previous one
                matml0->id(tempid);
            
        }

        /// <summary>
        /// Swap function with MatML Classes that have Optional Id.
        /// This has the added complication that the id's can not
        /// be duplicated during the swap.
        /// </summary>
        /// <typeparam name="MatML_Class"></typeparam>
        /// <param name="matml0"></param>
        /// <param name="matml1"></param>
        template<class MatML_Class>
        void  MatML_Base::SwapHavingOptionalId(
            observer_ptr < MatML_Class >& matml0,
            observer_ptr < MatML_Class >& matml1
        )
        {
            assert(matml0 && matml1);

            xml_schema::id temp_id0("");
            xml_schema::id temp_id1("");

            //temporarily store and remove the id to prevent id collision
            if (matml0->id().present()) {
                temp_id0 = matml0->id().get();
                matml0->id().reset();
            }
            if (matml1->id().present()) {
                temp_id1 = matml1->id().get();
                matml1->id().reset();
            }

            //perform the swap
            auto temp1( *matml1 );          
            *matml1 = *matml0;
            *matml0 = temp1;

            //Replace the id with the previous stored ones
            if (!temp_id0.empty())
                matml1->id().set(temp_id0);
            if (!temp_id1.empty())
                matml0->id().set(temp_id1);
        }


        template< 
            class MatML_ContClass,
            class MatML_Class
        >
        decltype(auto)
            MatML_Base::FindAndBumpUp(
                const observer_ptr < MatML_Class> element,
                MatML_ContClass& cont
            )
        {
            auto element_observer{ remove_strongly_typed_on_observer_ptr_v(element) };
            using element_type = remove_strongly_typed_on_observer_ptr_t<MatML_Class> ;
            using element_observer_type = typename std::remove_reference_t<decltype(element_observer)>;

            if (element_observer) {
                if (cont.empty() || cont.size() < 2)
                    return  std::make_pair(
                        observer_ptr<element_type>(),
                        observer_ptr<element_type>()
                    );

                auto is_equal = [&element_observer](element_type& matml) {return (void*)&matml == (void*)element_observer; };
                auto iter = std::find_if(cont.begin() + 1, cont.end(), is_equal);
                if (iter != cont.end()) {

                    observer_ptr<element_type> pair0(&*(iter - 1));
                    observer_ptr<element_type> pair1(&*(iter));
                    MatML_Base::Swap(pair0, pair1);
                    return std::make_pair(pair0, pair1);
                }
            }  
            return  std::make_pair(
                observer_ptr<element_type>(),
                observer_ptr<element_type>()
            );
        };


        /// <summary>
        /// Similar to MatMLFindAndBumpUp with the added complication 
        /// that the Required Id's cannot be duplicated during the swap.
        /// </summary>
        /// <typeparam name="MatML_ContClass"></typeparam>
        /// <param name="matml"></param>
        /// <param name="cont"></param>
        /// <returns></returns>
        template<
            class MatML_ContClass,
            class MatML_Class
        >
        std::pair<observer_ptr<MatML_Class>, observer_ptr<MatML_Class> >
            MatML_Base::FindAndBumpUpHavingId(
                const observer_ptr<MatML_Class> element,
                MatML_ContClass& cont
            )
        {
            if (element) {
                if (cont.empty() || cont.size() < 2)
                    return  std::make_pair(
                        observer_ptr<MatML_Class>(),
                        observer_ptr<MatML_Class>()
                    );

                auto is_equal = [&element](MatML_Class& matml) {return (void*)&matml == (void*)element; };

                auto iter = std::find_if(cont.begin() + 1, cont.end(), is_equal);
                if (iter != cont.end()) {

                    observer_ptr<MatML_Class> pair0 =(&*(iter - 1));
                    observer_ptr<MatML_Class> pair1=(&*(iter));
                    MatML_Base::SwapHavingId(pair0, pair1);
                    return std::make_pair(pair0, pair1);
                }
            }
            return  std::make_pair(
                observer_ptr<MatML_Class>(),
                observer_ptr<MatML_Class>()
            );
        }

        /// <summary>
        /// Similar to MatMLFindAndBumpUp with the added complication 
        /// that the optional Id's cannot be duplicated during the swap.
        /// </summary>
        /// <typeparam name="MatML_ContClass"></typeparam>
        /// <param name="matml"></param>
        /// <param name="cont"></param>
        /// <returns></returns>
        template<
            class MatML_ContClass,
            class MatML_Class
        >
        decltype(auto)
            MatML_Base::FindAndBumpUpHavingOptionalId(
                const observer_ptr<MatML_Class> element,
                MatML_ContClass& cont
            )
        {
            if (element) {
                if (cont.empty() || cont.size() < 2)
                    return  std::make_pair(
                        observer_ptr<MatML_Class>(),
                        observer_ptr<MatML_Class>()
                    );

                auto is_equal = [&element](MatML_Class& matml) {return (void*)&matml == (void*)element; };
                auto iter = std::find_if(cont.begin() + 1, cont.end(), is_equal);
                if (iter != cont.end()) {

                    observer_ptr<MatML_Class> pair0(&*(iter - 1));
                    observer_ptr<MatML_Class> pair1(&*(iter));
                    MatML_Base::SwapHavingOptionalId(pair0,pair1);
                    return std::make_pair(pair0, pair1);
                }
            }
            return  std::make_pair(
                observer_ptr<MatML_Class>(),
                observer_ptr<MatML_Class>()
            );
        }


        /// <summary>
        /// For the MatML Data finds the matching
        /// MatML Class element and bumps it down one.
        /// 
        /// Note: 
        /// - No strongtype allowed
        /// - weak_ptr
        /// 
        /// </summary>
        /// <typeparam name="MatML_Class"></typeparam>
        /// <typeparam name="MatML_ContClass"></typeparam>
        /// <param name="matml">Element to be found and bumped down</param>
        /// <param name="cont">Container of the element</param>
        /// <returns></returns>
        template< 
            class MatML_ContClass,
            class MatML_Class
        >
        decltype(auto)
            MatML_Base::FindAndBumpDown(
                const observer_ptr<MatML_Class>& element,
                MatML_ContClass& cont
            )
        {
            if (element) {

                if (cont.empty() || cont.size() < 2)
                    return std::make_pair(
                        observer_ptr<MatML_Class>(),
                        observer_ptr<MatML_Class>()
                );

                auto is_equal = [&element](MatML_Class& matml) {return (void*)&matml == (void*)element; };
                auto iter = std::find_if(cont.begin(), cont.end() - 1, is_equal);
                if (iter != cont.end() - 1) {

                    observer_ptr<MatML_Class> pair0 = (&*(iter));
                    observer_ptr<MatML_Class> pair1 = (&*(iter + 1));
                    MatML_Base::Swap(pair0, pair1);
                    return std::make_pair(pair0, pair1);
                }
            }
            return std::make_pair(
                observer_ptr<MatML_Class>(),
                observer_ptr<MatML_Class>()
            );
        }


        /// <summary>
        /// Similar to MatMLFindAndBumpDown with the added complication 
        /// that the Required Id's cannot be duplicated during the swap.
        /// </summary>
        /// <typeparam name="MatML_Class"></typeparam>
        /// <typeparam name="MatML_ContClass"></typeparam>
        /// <param name="matml"></param>
        /// <param name="cont"></param>
        /// <returns></returns>
        template<
            class MatML_ContClass,
            class MatML_Class
        >
        std::pair<observer_ptr<MatML_Class>,observer_ptr<MatML_Class> >
            MatML_Base::FindAndBumpDownHavingId(
                const observer_ptr < MatML_Class> element,
                MatML_ContClass& cont
            )
        {
            if (element) {
                if (cont.empty() || cont.size() < 2)
                    return std::make_pair(
                        observer_ptr<MatML_Class>(),
                        observer_ptr<MatML_Class>()
                );

                auto is_equal = [&element](MatML_Class& matml) {return (void*)&matml == (void*)element; };
                auto iter = std::find_if(cont.begin(), cont.end() - 1, is_equal);
                if (iter != cont.end() - 1) {
                    observer_ptr<MatML_Class> pair0=(&*(iter));
                    observer_ptr<MatML_Class> pair1=(&*(iter + 1));
                    MatML_Base::SwapHavingId(pair0, pair1);
                    return std::make_pair(pair0, pair1);
                }
            }  
            return std::make_pair(
                observer_ptr<MatML_Class>(),
                observer_ptr<MatML_Class>()
            );
        }


        /// <summary>
        /// Similar to MatMLFindAndBumpDown with the added complication 
        /// that the optional Id's cannot be duplicated during the swap.
        /// </summary>
        /// <typeparam name="MatML_Class"></typeparam>
        /// <typeparam name="MatML_ContClass"></typeparam>
        /// <param name="matml"></param>
        /// <param name="cont"></param>
        /// <returns></returns>
        template< 
            class MatML_ContClass,
            class MatML_Class
        >
        decltype(auto)
            MatML_Base::FindAndBumpDownHavingOptionalId(
               const observer_ptr < MatML_Class> element,
                MatML_ContClass& cont
            )
        {
            if (element) {
                if (cont.empty() || cont.size() < 2)
                    return std::make_pair(
                        observer_ptr<MatML_Class>(),
                        observer_ptr<MatML_Class>()
                );

                auto is_equal = [&element](MatML_Class& matml) {return (void*)&matml == (void*)element; };
                auto iter = std::find_if(cont.begin(), cont.end() - 1, is_equal);
                if (iter != cont.end() - 1) {
                    observer_ptr<MatML_Class> pair0=(&*(iter));
                    observer_ptr<MatML_Class> pair1=(&*(iter+1));
                    MatML_Base::SwapHavingOptionalId(pair0,pair1);
                    return std::make_pair(pair0,pair1);
                    
                }
            }
            return std::make_pair(
                observer_ptr<MatML_Class>(),
                observer_ptr<MatML_Class>()
            );
        }


};//end namespace bellshire
