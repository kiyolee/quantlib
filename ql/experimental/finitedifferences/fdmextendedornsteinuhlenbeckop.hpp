/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2011 Klaus Spanderen

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it
 under the terms of the QuantLib license.  You should have received a
 copy of the license along with this program; if not, please email
 <quantlib-dev@lists.sf.net>. The license is also available online at
 <http://quantlib.org/license.shtml>.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

/*! \file fdmextendedornsteinuhlenbeckop.hpp
    \brief Ornstein Uhlenbeck process plus jumps (Kluge Model)
*/

#ifndef quantlib_fdm_extended_ornsteinuhlenback_op_hpp
#define quantlib_fdm_extended_ornsteinuhlenback_op_hpp

#include <ql/methods/finitedifferences/operators/firstderivativeop.hpp>
#include <ql/methods/finitedifferences/operators/triplebandlinearop.hpp>
#include <ql/methods/finitedifferences/operators/fdmlinearopcomposite.hpp>
#include <ql/methods/finitedifferences/utilities/fdmboundaryconditionset.hpp>


namespace QuantLib {

    class FdmMesher;
    class YieldTermStructure;
    class ExtendedOrnsteinUhlenbeckProcess;

    class FdmExtendedOrnsteinUhlenbackOp : public FdmLinearOpComposite {
      public:
        FdmExtendedOrnsteinUhlenbackOp(
               const boost::shared_ptr<FdmMesher>& mesher,
               const boost::shared_ptr<ExtendedOrnsteinUhlenbeckProcess>& p,
               const boost::shared_ptr<YieldTermStructure>& rTS,
               const FdmBoundaryConditionSet& bcSet,
               Size direction = 0);

        Size size() const;
        void setTime(Time t1, Time t2);

        Disposable<Array> apply(const Array& r) const;
        Disposable<Array> apply_mixed(const Array& r) const;

        Disposable<Array> apply_direction(Size direction,
                                          const Array& r) const;
        Disposable<Array> solve_splitting(Size direction,
                                          const Array& r, Real s) const;
        Disposable<Array> preconditioner(const Array& r, Real s) const;

#if !defined(QL_NO_UBLAS_SUPPORT)
        Disposable<SparseMatrix> toMatrix() const;
#endif
      private:
        const boost::shared_ptr<FdmMesher> mesher_;
        const boost::shared_ptr<ExtendedOrnsteinUhlenbeckProcess> process_;
        const boost::shared_ptr<YieldTermStructure> rTS_;
        const FdmBoundaryConditionSet bcSet_;
        const Size direction_;

        const Array x_;
        const FirstDerivativeOp dxMap_;
        const TripleBandLinearOp dxxMap_;
        TripleBandLinearOp mapX_;

    };
}
#endif