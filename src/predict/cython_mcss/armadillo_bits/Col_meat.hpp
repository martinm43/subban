// SPDX-License-Identifier: Apache-2.0
// 
// Copyright 2008-2016 Conrad Sanderson (http://conradsanderson.id.au)
// Copyright 2008-2016 National ICT Australia (NICTA)
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ------------------------------------------------------------------------


//! \addtogroup Col
//! @{


//! construct an empty column vector
template<typename eT>
inline
Col<eT>::Col()
  : Mat<eT>(arma_vec_indicator(), 1)
  {
  arma_debug_sigprint();
  }



template<typename eT>
inline
Col<eT>::Col(const Col<eT>& X)
  : Mat<eT>(arma_vec_indicator(), X.n_elem, 1, 1)
  {
  arma_debug_sigprint();
  
  arrayops::copy((*this).memptr(), X.memptr(), X.n_elem);
  }



//! construct a column vector with the specified number of n_elem
template<typename eT>
inline
Col<eT>::Col(const uword in_n_elem)
  : Mat<eT>(arma_vec_indicator(), in_n_elem, 1, 1)
  {
  arma_debug_sigprint();
  
  arma_debug_print("Col::constructor: zeroing memory");
  
  arrayops::fill_zeros(Mat<eT>::memptr(), Mat<eT>::n_elem);
  }



template<typename eT>
inline
Col<eT>::Col(const uword in_n_rows, const uword in_n_cols)
  : Mat<eT>(arma_vec_indicator(), 0, 0, 1)
  {
  arma_debug_sigprint();
  
  Mat<eT>::init_warm(in_n_rows, in_n_cols);
  
  arma_debug_print("Col::constructor: zeroing memory");
  
  arrayops::fill_zeros(Mat<eT>::memptr(), Mat<eT>::n_elem);
  }



template<typename eT>
inline
Col<eT>::Col(const SizeMat& s)
  : Mat<eT>(arma_vec_indicator(), 0, 0, 1)
  {
  arma_debug_sigprint();
  
  Mat<eT>::init_warm(s.n_rows, s.n_cols);
  
  arma_debug_print("Col::constructor: zeroing memory");
  
  arrayops::fill_zeros(Mat<eT>::memptr(), Mat<eT>::n_elem);
  }



//! internal use only
template<typename eT>
template<bool do_zeros>
inline
Col<eT>::Col(const uword in_n_elem, const arma_initmode_indicator<do_zeros>&)
  : Mat<eT>(arma_vec_indicator(), in_n_elem, 1, 1)
  {
  arma_debug_sigprint();
  
  if(do_zeros)
    {
    arma_debug_print("Col::constructor: zeroing memory");
    arrayops::fill_zeros(Mat<eT>::memptr(), Mat<eT>::n_elem);
    }
  else
    {
    arma_debug_print("Col::constructor: not zeroing memory");
    }
  }



//! internal use only
template<typename eT>
template<bool do_zeros>
inline
Col<eT>::Col(const uword in_n_rows, const uword in_n_cols, const arma_initmode_indicator<do_zeros>&)
  : Mat<eT>(arma_vec_indicator(), 0, 0, 1)
  {
  arma_debug_sigprint();
  
  Mat<eT>::init_warm(in_n_rows, in_n_cols);
  
  if(do_zeros)
    {
    arma_debug_print("Col::constructor: zeroing memory");
    arrayops::fill_zeros(Mat<eT>::memptr(), Mat<eT>::n_elem);
    }
  else
    {
    arma_debug_print("Col::constructor: not zeroing memory");
    }
  }



//! internal use only
template<typename eT>
template<bool do_zeros>
inline
Col<eT>::Col(const SizeMat& s, const arma_initmode_indicator<do_zeros>&)
  : Mat<eT>(arma_vec_indicator(), 0, 0, 1)
  {
  arma_debug_sigprint();
  
  Mat<eT>::init_warm(s.n_rows, s.n_cols);
  
  if(do_zeros)
    {
    arma_debug_print("Col::constructor: zeroing memory");
    arrayops::fill_zeros(Mat<eT>::memptr(), Mat<eT>::n_elem);
    }
  else
    {
    arma_debug_print("Col::constructor: not zeroing memory");
    }
  }



template<typename eT>
template<typename fill_type>
inline
Col<eT>::Col(const uword in_n_elem, const fill::fill_class<fill_type>& f)
  : Mat<eT>(arma_vec_indicator(), in_n_elem, 1, 1)
  {
  arma_debug_sigprint();
  
  (*this).fill(f);
  }



template<typename eT>
template<typename fill_type>
inline
Col<eT>::Col(const uword in_n_rows, const uword in_n_cols, const fill::fill_class<fill_type>& f)
  : Mat<eT>(arma_vec_indicator(), 0, 0, 1)
  {
  arma_debug_sigprint();
  
  Mat<eT>::init_warm(in_n_rows, in_n_cols);
  
  (*this).fill(f);
  }



template<typename eT>
template<typename fill_type>
inline
Col<eT>::Col(const SizeMat& s, const fill::fill_class<fill_type>& f)
  : Mat<eT>(arma_vec_indicator(), 0, 0, 1)
  {
  arma_debug_sigprint();
  
  Mat<eT>::init_warm(s.n_rows, s.n_cols);
  
  (*this).fill(f);
  }



template<typename eT>
inline
Col<eT>::Col(const uword in_n_elem, const fill::scalar_holder<eT> f)
  : Mat<eT>(arma_vec_indicator(), in_n_elem, 1, 1)
  {
  arma_debug_sigprint();
  
  (*this).fill(f.scalar);
  }



template<typename eT>
inline
Col<eT>::Col(const uword in_n_rows, const uword in_n_cols, const fill::scalar_holder<eT> f)
  : Mat<eT>(arma_vec_indicator(), 0, 0, 1)
  {
  arma_debug_sigprint();
  
  Mat<eT>::init_warm(in_n_rows, in_n_cols);
  
  (*this).fill(f.scalar);
  }



template<typename eT>
inline
Col<eT>::Col(const SizeMat& s, const fill::scalar_holder<eT> f)
  : Mat<eT>(arma_vec_indicator(), 0, 0, 1)
  {
  arma_debug_sigprint();
  
  Mat<eT>::init_warm(s.n_rows, s.n_cols);
  
  (*this).fill(f.scalar);
  }



template<typename eT>
inline
Col<eT>::Col(const char* text)
  : Mat<eT>(arma_vec_indicator(), 1)
  {
  arma_debug_sigprint();
  
  (*this).operator=(text);
  }



template<typename eT>
inline
Col<eT>&
Col<eT>::operator=(const char* text)
  {
  arma_debug_sigprint();
  
  Mat<eT> tmp(text);
  
  arma_conform_check( ((tmp.n_elem > 0) && (tmp.is_vec() == false)), "Mat::init(): requested size is not compatible with column vector layout" );
  
  access::rw(tmp.n_rows) = tmp.n_elem;
  access::rw(tmp.n_cols) = 1;
  
  (*this).steal_mem(tmp);
  
  return *this;
  }



template<typename eT>
inline
Col<eT>::Col(const std::string& text)
  : Mat<eT>(arma_vec_indicator(), 1)
  {
  arma_debug_sigprint();
  
  (*this).operator=(text);
  }



template<typename eT>
inline
Col<eT>&
Col<eT>::operator=(const std::string& text)
  {
  arma_debug_sigprint();
  
  Mat<eT> tmp(text);
  
  arma_conform_check( ((tmp.n_elem > 0) && (tmp.is_vec() == false)), "Mat::init(): requested size is not compatible with column vector layout" );
  
  access::rw(tmp.n_rows) = tmp.n_elem;
  access::rw(tmp.n_cols) = 1;
  
  (*this).steal_mem(tmp);
  
  return *this;
  }



//! create a column vector from std::vector
template<typename eT>
inline
Col<eT>::Col(const std::vector<eT>& x)
  : Mat<eT>(arma_vec_indicator(), uword(x.size()), 1, 1)
  {
  arma_debug_sigprint_this(this);
  
  const uword N = uword(x.size());
  
  if(N > 0)  { arrayops::copy( Mat<eT>::memptr(), &(x[0]), N ); }
  }
  
  
  
//! create a column vector from std::vector
template<typename eT>
inline
Col<eT>&
Col<eT>::operator=(const std::vector<eT>& x)
  {
  arma_debug_sigprint();
  
  const uword N = uword(x.size());
  
  Mat<eT>::init_warm(N, 1);
  
  if(N > 0)  { arrayops::copy( Mat<eT>::memptr(), &(x[0]), N ); }
  
  return *this;
  }



template<typename eT>
inline
Col<eT>::Col(const std::initializer_list<eT>& list)
  : Mat<eT>(arma_vec_indicator(), uword(list.size()), 1, 1)
  {
  arma_debug_sigprint_this(this);
  
  const uword N = uword(list.size());
  
  if(N > 0)  { arrayops::copy( Mat<eT>::memptr(), list.begin(), N ); }
  }



template<typename eT>
inline
Col<eT>&
Col<eT>::operator=(const std::initializer_list<eT>& list)
  {
  arma_debug_sigprint();
  
  const uword N = uword(list.size());
  
  Mat<eT>::init_warm(N, 1);
  
  if(N > 0)  { arrayops::copy( Mat<eT>::memptr(), list.begin(), N ); }
  
  return *this;
  }



template<typename eT>
inline
Col<eT>::Col(Col<eT>&& X)
  : Mat<eT>(arma_vec_indicator(), 1)
  {
  arma_debug_sigprint(arma_str::format("this: %x; X: %x") % this % &X);
  
  access::rw(Mat<eT>::n_rows)  = X.n_rows;
  access::rw(Mat<eT>::n_cols)  = 1;
  access::rw(Mat<eT>::n_elem)  = X.n_elem;
  access::rw(Mat<eT>::n_alloc) = X.n_alloc;
  
  if( (X.n_alloc > arma_config::mat_prealloc) || (X.mem_state == 1) || (X.mem_state == 2) )
    {
    access::rw(Mat<eT>::mem_state) = X.mem_state;
    access::rw(Mat<eT>::mem)       = X.mem;
    
    access::rw(X.n_rows)    = 0;
    access::rw(X.n_cols)    = 1;
    access::rw(X.n_elem)    = 0;
    access::rw(X.n_alloc)   = 0;
    access::rw(X.mem_state) = 0;
    access::rw(X.mem)       = nullptr;
    }
  else  // condition: (X.n_alloc <= arma_config::mat_prealloc) || (X.mem_state == 0) || (X.mem_state == 3)
    {
    (*this).init_cold();
    
    arrayops::copy( (*this).memptr(), X.mem, X.n_elem );
    
    if( (X.mem_state == 0) && (X.n_alloc <= arma_config::mat_prealloc) )
      {
      access::rw(X.n_rows)  = 0;
      access::rw(X.n_cols)  = 1;
      access::rw(X.n_elem)  = 0;
      access::rw(X.mem)     = nullptr;
      }
    }
  }



template<typename eT>
inline
Col<eT>&
Col<eT>::operator=(Col<eT>&& X)
  {
  arma_debug_sigprint(arma_str::format("this: %x; X: %x") % this % &X);
  
  (*this).steal_mem(X, true);
  
  return *this;
  }



// template<typename eT>
// inline
// Col<eT>::Col(Mat<eT>&& X)
//   : Mat<eT>(arma_vec_indicator(), 1)
//   {
//   arma_debug_sigprint(arma_str::format("this: %x; X: %x") % this % &X);
//   
//   if(X.n_cols != 1)  { const Mat<eT>& XX = X; Mat<eT>::operator=(XX); return; }
//   
//   access::rw(Mat<eT>::n_rows)  = X.n_rows;
//   access::rw(Mat<eT>::n_cols)  = 1;
//   access::rw(Mat<eT>::n_elem)  = X.n_elem;
//   access::rw(Mat<eT>::n_alloc) = X.n_alloc;
//   
//   if( (X.n_alloc > arma_config::mat_prealloc) || (X.mem_state == 1) || (X.mem_state == 2) )
//     {
//     access::rw(Mat<eT>::mem_state) = X.mem_state;
//     access::rw(Mat<eT>::mem)       = X.mem;
//     
//     access::rw(X.n_rows)    = 0;
//     access::rw(X.n_elem)    = 0;
//     access::rw(X.n_alloc)   = 0;
//     access::rw(X.mem_state) = 0;
//     access::rw(X.mem)       = nullptr;
//     }
//   else  // condition: (X.n_alloc <= arma_config::mat_prealloc) || (X.mem_state == 0) || (X.mem_state == 3)
//     {
//     (*this).init_cold();
//     
//     arrayops::copy( (*this).memptr(), X.mem, X.n_elem );
//     
//     if( (X.mem_state == 0) && (X.n_alloc <= arma_config::mat_prealloc) )
//       {
//       access::rw(X.n_rows)  = 0;
//       access::rw(X.n_elem)  = 0;
//       access::rw(X.mem)     = nullptr;
//       }
//     }
//   }
// 
// 
// 
// template<typename eT>
// inline
// Col<eT>&
// Col<eT>::operator=(Mat<eT>&& X)
//   {
//   arma_debug_sigprint(arma_str::format("this: %x; X: %x") % this % &X);
//   
//   if(X.n_cols != 1)  { const Mat<eT>& XX = X; Mat<eT>::operator=(XX); return *this; }
//   
//   (*this).steal_mem(X, true);
//   
//   return *this;
//   }



template<typename eT>
inline
Col<eT>&
Col<eT>::operator=(const eT val)
  {
  arma_debug_sigprint();
  
  Mat<eT>::operator=(val);
  
  return *this;
  }



template<typename eT>
inline
Col<eT>&
Col<eT>::operator=(const Col<eT>& X)
  {
  arma_debug_sigprint();
  
  Mat<eT>::operator=(X);
  
  return *this;
  }



template<typename eT>
template<typename T1>
inline
Col<eT>::Col(const Base<eT,T1>& X)
  : Mat<eT>(arma_vec_indicator(), 1)
  {
  arma_debug_sigprint();
  
  Mat<eT>::operator=(X.get_ref());
  }



template<typename eT>
template<typename T1>
inline
Col<eT>&
Col<eT>::operator=(const Base<eT,T1>& X)
  {
  arma_debug_sigprint();
  
  Mat<eT>::operator=(X.get_ref());
  
  return *this;
  }



template<typename eT>
template<typename T1>
inline
Col<eT>::Col(const SpBase<eT,T1>& X)
  : Mat<eT>(arma_vec_indicator(), 1)
  {
  arma_debug_sigprint_this(this);
  
  Mat<eT>::operator=(X.get_ref());
  }



template<typename eT>
template<typename T1>
inline
Col<eT>&
Col<eT>::operator=(const SpBase<eT,T1>& X)
  {
  arma_debug_sigprint();
  
  Mat<eT>::operator=(X.get_ref());
  
  return *this;
  }



//! construct a column vector from a given auxiliary array of eTs
template<typename eT>
inline
Col<eT>::Col(eT* aux_mem, const uword aux_length, const bool copy_aux_mem, const bool strict)
  : Mat<eT>(aux_mem, aux_length, 1, copy_aux_mem, strict)
  {
  arma_debug_sigprint();
  
  access::rw(Mat<eT>::vec_state) = 1;
  }



//! construct a column vector from a given auxiliary array of eTs
template<typename eT>
inline
Col<eT>::Col(const eT* aux_mem, const uword aux_length)
  : Mat<eT>(aux_mem, aux_length, 1)
  {
  arma_debug_sigprint();
  
  access::rw(Mat<eT>::vec_state) = 1;
  }



template<typename eT>
template<typename T1, typename T2>
inline
Col<eT>::Col
  (
  const Base<typename Col<eT>::pod_type, T1>& A,
  const Base<typename Col<eT>::pod_type, T2>& B
  )
  {
  arma_debug_sigprint();
  
  access::rw(Mat<eT>::vec_state) = 1;
  
  Mat<eT>::init(A,B);
  }



template<typename eT>
template<typename T1>
inline
Col<eT>::Col(const BaseCube<eT,T1>& X)
  {
  arma_debug_sigprint();
  
  access::rw(Mat<eT>::vec_state) = 1;
  
  Mat<eT>::operator=(X);
  }



template<typename eT>
template<typename T1>
inline
Col<eT>&
Col<eT>::operator=(const BaseCube<eT,T1>& X)
  {
  arma_debug_sigprint();
  
  Mat<eT>::operator=(X);
  
  return *this;
  }



template<typename eT>
inline
Col<eT>::Col(const subview_cube<eT>& X)
  {
  arma_debug_sigprint();
  
  access::rw(Mat<eT>::vec_state) = 1;
  
  Mat<eT>::operator=(X);
  }



template<typename eT>
inline
Col<eT>&
Col<eT>::operator=(const subview_cube<eT>& X)
  {
  arma_debug_sigprint();
  
  Mat<eT>::operator=(X);
  
  return *this;
  }



template<typename eT>
inline
mat_injector< Col<eT> >
Col<eT>::operator<<(const eT val)
  {
  return mat_injector< Col<eT> >(*this, val);
  }



template<typename eT>
arma_inline
const Op<Col<eT>,op_htrans>
Col<eT>::t() const
  {
  return Op<Col<eT>,op_htrans>(*this);
  }



template<typename eT>
arma_inline
const Op<Col<eT>,op_htrans>
Col<eT>::ht() const
  {
  return Op<Col<eT>,op_htrans>(*this);
  }



template<typename eT>
arma_inline
const Op<Col<eT>,op_strans>
Col<eT>::st() const
  {
  return Op<Col<eT>,op_strans>(*this);
  }



template<typename eT>
arma_inline
const Op<Col<eT>,op_strans>
Col<eT>::as_row() const
  {
  return Op<Col<eT>,op_strans>(*this);
  }



template<typename eT>
arma_inline
subview_col<eT>
Col<eT>::row(const uword in_row1)
  {
  arma_debug_sigprint();
  
  arma_conform_check_bounds( (in_row1 >= Mat<eT>::n_rows), "Col::row(): indices out of bounds or incorrectly used" );
  
  return subview_col<eT>(*this, 0, in_row1, 1);
  }



template<typename eT>
arma_inline
const subview_col<eT>
Col<eT>::row(const uword in_row1) const
  {
  arma_debug_sigprint();
  
  arma_conform_check_bounds( (in_row1 >= Mat<eT>::n_rows), "Col::row(): indices out of bounds or incorrectly used" );
  
  return subview_col<eT>(*this, 0, in_row1, 1);
  }



template<typename eT>
arma_inline
subview_col<eT>
Col<eT>::rows(const uword in_row1, const uword in_row2)
  {
  arma_debug_sigprint();
  
  arma_conform_check_bounds( ( (in_row1 > in_row2) || (in_row2 >= Mat<eT>::n_rows) ), "Col::rows(): indices out of bounds or incorrectly used" );
  
  const uword subview_n_rows = in_row2 - in_row1 + 1;
  
  return subview_col<eT>(*this, 0, in_row1, subview_n_rows);
  }



template<typename eT>
arma_inline
const subview_col<eT>
Col<eT>::rows(const uword in_row1, const uword in_row2) const
  {
  arma_debug_sigprint();
  
  arma_conform_check_bounds( ( (in_row1 > in_row2) || (in_row2 >= Mat<eT>::n_rows) ), "Col::rows(): indices out of bounds or incorrectly used" );
  
  const uword subview_n_rows = in_row2 - in_row1 + 1;
  
  return subview_col<eT>(*this, 0, in_row1, subview_n_rows);
  }



template<typename eT>
arma_inline
subview_col<eT>
Col<eT>::subvec(const uword in_row1, const uword in_row2)
  {
  arma_debug_sigprint();
  
  arma_conform_check_bounds( ( (in_row1 > in_row2) || (in_row2 >= Mat<eT>::n_rows) ), "Col::subvec(): indices out of bounds or incorrectly used" );
  
  const uword subview_n_rows = in_row2 - in_row1 + 1;
  
  return subview_col<eT>(*this, 0, in_row1, subview_n_rows);
  }



template<typename eT>
arma_inline
const subview_col<eT>
Col<eT>::subvec(const uword in_row1, const uword in_row2) const
  {
  arma_debug_sigprint();
  
  arma_conform_check_bounds( ( (in_row1 > in_row2) || (in_row2 >= Mat<eT>::n_rows) ), "Col::subvec(): indices out of bounds or incorrectly used" );
  
  const uword subview_n_rows = in_row2 - in_row1 + 1;
  
  return subview_col<eT>(*this, 0, in_row1, subview_n_rows);
  }



template<typename eT>
arma_inline
subview_col<eT>
Col<eT>::rows(const span& row_span)
  {
  arma_debug_sigprint();
  
  return subvec(row_span);
  }



template<typename eT>
arma_inline
const subview_col<eT>
Col<eT>::rows(const span& row_span) const
  {
  arma_debug_sigprint();
  
  return subvec(row_span);
  }



template<typename eT>
arma_inline
subview_col<eT>
Col<eT>::subvec(const span& row_span)
  {
  arma_debug_sigprint();
  
  const bool row_all = row_span.whole;

  const uword local_n_rows = Mat<eT>::n_rows;
  
  const uword in_row1       = row_all ? 0            : row_span.a;
  const uword in_row2       =                          row_span.b;
  const uword subvec_n_rows = row_all ? local_n_rows : in_row2 - in_row1 + 1;

  arma_conform_check_bounds( ( row_all ? false : ((in_row1 > in_row2) || (in_row2 >= local_n_rows)) ), "Col::subvec(): indices out of bounds or incorrectly used" );
  
  return subview_col<eT>(*this, 0, in_row1, subvec_n_rows);
  }



template<typename eT>
arma_inline
const subview_col<eT>
Col<eT>::subvec(const span& row_span) const
  {
  arma_debug_sigprint();
  
  const bool row_all = row_span.whole;

  const uword local_n_rows = Mat<eT>::n_rows;
  
  const uword in_row1       = row_all ? 0            : row_span.a;
  const uword in_row2       =                          row_span.b;
  const uword subvec_n_rows = row_all ? local_n_rows : in_row2 - in_row1 + 1;

  arma_conform_check_bounds( ( row_all ? false : ((in_row1 > in_row2) || (in_row2 >= local_n_rows)) ), "Col::subvec(): indices out of bounds or incorrectly used" );
  
  return subview_col<eT>(*this, 0, in_row1, subvec_n_rows);
  }



template<typename eT>
arma_inline
subview_col<eT>
Col<eT>::operator()(const span& row_span)
  {
  arma_debug_sigprint();
  
  return subvec(row_span);
  }



template<typename eT>
arma_inline
const subview_col<eT>
Col<eT>::operator()(const span& row_span) const
  {
  arma_debug_sigprint();
  
  return subvec(row_span);
  }



template<typename eT>
arma_inline
subview_col<eT>
Col<eT>::subvec(const uword start_row, const SizeMat& s)
  {
  arma_debug_sigprint();
  
  arma_conform_check( (s.n_cols != 1), "Col::subvec(): given size does not specify a column vector" );
  
  arma_conform_check_bounds( ( (start_row >= Mat<eT>::n_rows) || ((start_row + s.n_rows) > Mat<eT>::n_rows) ), "Col::subvec(): size out of bounds" );
  
  return subview_col<eT>(*this, 0, start_row, s.n_rows);
  }



template<typename eT>
arma_inline
const subview_col<eT>
Col<eT>::subvec(const uword start_row, const SizeMat& s) const
  {
  arma_debug_sigprint();
  
  arma_conform_check( (s.n_cols != 1), "Col::subvec(): given size does not specify a column vector" );
  
  arma_conform_check_bounds( ( (start_row >= Mat<eT>::n_rows) || ((start_row + s.n_rows) > Mat<eT>::n_rows) ), "Col::subvec(): size out of bounds" );
  
  return subview_col<eT>(*this, 0, start_row, s.n_rows);
  }



template<typename eT>
arma_inline
subview_col<eT>
Col<eT>::head(const uword N)
  {
  arma_debug_sigprint();
  
  arma_conform_check_bounds( (N > Mat<eT>::n_rows), "Col::head(): size out of bounds" );
  
  return subview_col<eT>(*this, 0, 0, N);
  }



template<typename eT>
arma_inline
const subview_col<eT>
Col<eT>::head(const uword N) const
  {
  arma_debug_sigprint();
  
  arma_conform_check_bounds( (N > Mat<eT>::n_rows), "Col::head(): size out of bounds" );
  
  return subview_col<eT>(*this, 0, 0, N);
  }



template<typename eT>
arma_inline
subview_col<eT>
Col<eT>::tail(const uword N)
  {
  arma_debug_sigprint();
  
  arma_conform_check_bounds( (N > Mat<eT>::n_rows), "Col::tail(): size out of bounds" );
  
  const uword start_row = Mat<eT>::n_rows - N;
  
  return subview_col<eT>(*this, 0, start_row, N);
  }



template<typename eT>
arma_inline
const subview_col<eT>
Col<eT>::tail(const uword N) const
  {
  arma_debug_sigprint();
  
  arma_conform_check_bounds( (N > Mat<eT>::n_rows), "Col::tail(): size out of bounds" );
  
  const uword start_row = Mat<eT>::n_rows - N;
  
  return subview_col<eT>(*this, 0, start_row, N);
  }



template<typename eT>
arma_inline
subview_col<eT>
Col<eT>::head_rows(const uword N)
  {
  arma_debug_sigprint();
  
  return (*this).head(N);
  }



template<typename eT>
arma_inline
const subview_col<eT>
Col<eT>::head_rows(const uword N) const
  {
  arma_debug_sigprint();
  
  return (*this).head(N);
  }



template<typename eT>
arma_inline
subview_col<eT>
Col<eT>::tail_rows(const uword N)
  {
  arma_debug_sigprint();
  
  return (*this).tail(N);
  }



template<typename eT>
arma_inline
const subview_col<eT>
Col<eT>::tail_rows(const uword N) const
  {
  arma_debug_sigprint();
  
  return (*this).tail(N);
  }



//! remove specified row
template<typename eT>
inline
void
Col<eT>::shed_row(const uword row_num)
  {
  arma_debug_sigprint();
  
  arma_conform_check_bounds( row_num >= Mat<eT>::n_rows, "Col::shed_row(): index out of bounds" );
  
  shed_rows(row_num, row_num);
  }



//! remove specified rows
template<typename eT>
inline
void
Col<eT>::shed_rows(const uword in_row1, const uword in_row2)
  {
  arma_debug_sigprint();
  
  arma_conform_check_bounds
    (
    (in_row1 > in_row2) || (in_row2 >= Mat<eT>::n_rows),
    "Col::shed_rows(): indices out of bounds or incorrectly used"
    );
  
  const uword n_keep_front = in_row1;
  const uword n_keep_back  = Mat<eT>::n_rows - (in_row2 + 1);
  
  Col<eT> X(n_keep_front + n_keep_back, arma_nozeros_indicator());
  
        eT* X_mem = X.memptr();
  const eT* t_mem = (*this).memptr();
  
  if(n_keep_front > 0)
    {
    arrayops::copy( X_mem, t_mem, n_keep_front );
    }
  
  if(n_keep_back > 0)
    {
    arrayops::copy( &(X_mem[n_keep_front]), &(t_mem[in_row2+1]), n_keep_back);
    }
  
  Mat<eT>::steal_mem(X);
  }



//! remove specified rows
template<typename eT>
template<typename T1>
inline
void
Col<eT>::shed_rows(const Base<uword, T1>& indices)
  {
  arma_debug_sigprint();
  
  Mat<eT>::shed_rows(indices);
  }



template<typename eT>
inline
void
Col<eT>::insert_rows(const uword row_num, const uword N, const bool set_to_zero)
  {
  arma_debug_sigprint();
  
  arma_ignore(set_to_zero);
  
  (*this).insert_rows(row_num, N);
  }



template<typename eT>
inline
void
Col<eT>::insert_rows(const uword row_num, const uword N)
  {
  arma_debug_sigprint();
  
  const uword t_n_rows = Mat<eT>::n_rows;
  
  const uword A_n_rows = row_num;
  const uword B_n_rows = t_n_rows - row_num;
  
  // insertion at row_num == n_rows is in effect an append operation
  arma_conform_check_bounds( (row_num > t_n_rows), "Col::insert_rows(): index out of bounds" );
  
  if(N == 0)  { return; }
  
  Col<eT> out(t_n_rows + N, arma_nozeros_indicator());
  
        eT* out_mem = out.memptr();
  const eT*   t_mem = (*this).memptr();
  
  if(A_n_rows > 0)
    {
    arrayops::copy( out_mem, t_mem, A_n_rows );
    }
  
  if(B_n_rows > 0)
    {
    arrayops::copy( &(out_mem[row_num + N]), &(t_mem[row_num]), B_n_rows );
    }
  
  arrayops::fill_zeros( &(out_mem[row_num]), N );
  
  Mat<eT>::steal_mem(out);
  }



//! insert the given object at the specified row position; 
//! the given object must have one column
template<typename eT>
template<typename T1>
inline
void
Col<eT>::insert_rows(const uword row_num, const Base<eT,T1>& X)
  {
  arma_debug_sigprint();
  
  Mat<eT>::insert_rows(row_num, X);
  }



template<typename eT>
arma_inline
eT&
Col<eT>::at(const uword i)
  {
  return access::rw(Mat<eT>::mem[i]);
  }



template<typename eT>
arma_inline
const eT&
Col<eT>::at(const uword i) const
  {
  return Mat<eT>::mem[i];
  }



template<typename eT>
arma_inline
eT&
Col<eT>::at(const uword in_row, const uword)
  {
  return access::rw( Mat<eT>::mem[in_row] );
  }



template<typename eT>
arma_inline
const eT&
Col<eT>::at(const uword in_row, const uword) const
  {
  return Mat<eT>::mem[in_row];
  }



template<typename eT>
inline
typename Col<eT>::row_iterator
Col<eT>::begin_row(const uword row_num)
  {
  arma_debug_sigprint();
  
  arma_conform_check_bounds( (row_num >= Mat<eT>::n_rows), "Col::begin_row(): index out of bounds" );
  
  return Mat<eT>::memptr() + row_num;
  }



template<typename eT>
inline
typename Col<eT>::const_row_iterator
Col<eT>::begin_row(const uword row_num) const
  {
  arma_debug_sigprint();
  
  arma_conform_check_bounds( (row_num >= Mat<eT>::n_rows), "Col::begin_row(): index out of bounds" );
  
  return Mat<eT>::memptr() + row_num;
  }



template<typename eT>
inline
typename Col<eT>::row_iterator
Col<eT>::end_row(const uword row_num)
  {
  arma_debug_sigprint();
  
  arma_conform_check_bounds( (row_num >= Mat<eT>::n_rows), "Col::end_row(): index out of bounds" );
  
  return Mat<eT>::memptr() + row_num + 1;
  }



template<typename eT>
inline
typename Col<eT>::const_row_iterator
Col<eT>::end_row(const uword row_num) const
  {
  arma_debug_sigprint();
  
  arma_conform_check_bounds( (row_num >= Mat<eT>::n_rows), "Col::end_row(): index out of bounds" );
  
  return Mat<eT>::memptr() + row_num + 1;
  }



template<typename eT>
template<uword fixed_n_elem>
arma_inline
Col<eT>::fixed<fixed_n_elem>::fixed()
  : Col<eT>( arma_fixed_indicator(), fixed_n_elem, ((use_extra) ? mem_local_extra : Mat<eT>::mem_local) )
  {
  arma_debug_sigprint_this(this);
  
  arma_debug_print("Col::fixed::constructor: zeroing memory");
  
  eT* mem_use = (use_extra) ? &(mem_local_extra[0]) : &(Mat<eT>::mem_local[0]);
  
  arrayops::inplace_set_fixed<eT,fixed_n_elem>( mem_use, eT(0) );
  }



template<typename eT>
template<uword fixed_n_elem>
arma_inline
Col<eT>::fixed<fixed_n_elem>::fixed(const fixed<fixed_n_elem>& X)
  : Col<eT>( arma_fixed_indicator(), fixed_n_elem, ((use_extra) ? mem_local_extra : Mat<eT>::mem_local) )
  {
  arma_debug_sigprint_this(this);
  
        eT* dest = (use_extra) ?   mem_local_extra : Mat<eT>::mem_local;
  const eT* src  = (use_extra) ? X.mem_local_extra :        X.mem_local;
  
  arrayops::copy( dest, src, fixed_n_elem );
  }



template<typename eT>
template<uword fixed_n_elem>
arma_inline
Col<eT>::fixed<fixed_n_elem>::fixed(const subview_cube<eT>& X)
  : Col<eT>( arma_fixed_indicator(), fixed_n_elem, ((use_extra) ? mem_local_extra : Mat<eT>::mem_local) )
  {
  arma_debug_sigprint_this(this);
  
  Col<eT>::operator=(X);
  }



template<typename eT>
template<uword fixed_n_elem>
inline
Col<eT>::fixed<fixed_n_elem>::fixed(const fill::scalar_holder<eT> f)
  : Col<eT>( arma_fixed_indicator(), fixed_n_elem, ((use_extra) ? mem_local_extra : Mat<eT>::mem_local) )
  {
  arma_debug_sigprint_this(this);
  
  (*this).fill(f.scalar);
  }



template<typename eT>
template<uword fixed_n_elem>
template<typename fill_type>
inline
Col<eT>::fixed<fixed_n_elem>::fixed(const fill::fill_class<fill_type>&)
  : Col<eT>( arma_fixed_indicator(), fixed_n_elem, ((use_extra) ? mem_local_extra : Mat<eT>::mem_local) )
  {
  arma_debug_sigprint_this(this);
  
  if(is_same_type<fill_type, fill::fill_zeros>::yes)  {  (*this).zeros(); }
  if(is_same_type<fill_type, fill::fill_ones >::yes)  {  (*this).ones();  }
  if(is_same_type<fill_type, fill::fill_eye  >::yes)  { Mat<eT>::eye();   }
  if(is_same_type<fill_type, fill::fill_randu>::yes)  { Mat<eT>::randu(); }
  if(is_same_type<fill_type, fill::fill_randn>::yes)  { Mat<eT>::randn(); }
  }



template<typename eT>
template<uword fixed_n_elem>
template<typename T1>
arma_inline
Col<eT>::fixed<fixed_n_elem>::fixed(const Base<eT,T1>& A)
  : Col<eT>( arma_fixed_indicator(), fixed_n_elem, ((use_extra) ? mem_local_extra : Mat<eT>::mem_local) )
  {
  arma_debug_sigprint_this(this);
  
  Col<eT>::operator=(A.get_ref());
  }



template<typename eT>
template<uword fixed_n_elem>
template<typename T1, typename T2>
arma_inline
Col<eT>::fixed<fixed_n_elem>::fixed(const Base<pod_type,T1>& A, const Base<pod_type,T2>& B)
  : Col<eT>( arma_fixed_indicator(), fixed_n_elem, ((use_extra) ? mem_local_extra : Mat<eT>::mem_local) )
  {
  arma_debug_sigprint_this(this);
  
  Col<eT>::init(A,B);
  }



template<typename eT>
template<uword fixed_n_elem>
inline
Col<eT>::fixed<fixed_n_elem>::fixed(const eT* aux_mem)
  : Col<eT>( arma_fixed_indicator(), fixed_n_elem, ((use_extra) ? mem_local_extra : Mat<eT>::mem_local) )
  {
  arma_debug_sigprint_this(this);
  
  eT* dest = (use_extra) ? mem_local_extra : Mat<eT>::mem_local;
  
  arrayops::copy( dest, aux_mem, fixed_n_elem );
  }



template<typename eT>
template<uword fixed_n_elem>
inline
Col<eT>::fixed<fixed_n_elem>::fixed(const char* text)
  : Col<eT>( arma_fixed_indicator(), fixed_n_elem, ((use_extra) ? mem_local_extra : Mat<eT>::mem_local) )
  {
  arma_debug_sigprint_this(this);
  
  Col<eT>::operator=(text);
  }



template<typename eT>
template<uword fixed_n_elem>
inline
Col<eT>::fixed<fixed_n_elem>::fixed(const std::string& text)
  : Col<eT>( arma_fixed_indicator(), fixed_n_elem, ((use_extra) ? mem_local_extra : Mat<eT>::mem_local) )
  {
  arma_debug_sigprint_this(this);
  
  Col<eT>::operator=(text);
  }



template<typename eT>
template<uword fixed_n_elem>
template<typename T1>
Col<eT>&
Col<eT>::fixed<fixed_n_elem>::operator=(const Base<eT,T1>& A)
  {
  arma_debug_sigprint();
  
  Col<eT>::operator=(A.get_ref());
  
  return *this;
  }



template<typename eT>
template<uword fixed_n_elem>
Col<eT>&
Col<eT>::fixed<fixed_n_elem>::operator=(const eT val)
  {
  arma_debug_sigprint();
  
  Col<eT>::operator=(val);
  
  return *this;
  }



template<typename eT>
template<uword fixed_n_elem>
Col<eT>&
Col<eT>::fixed<fixed_n_elem>::operator=(const char* text)
  {
  arma_debug_sigprint();
  
  Col<eT>::operator=(text);
  
  return *this; 
  }



template<typename eT>
template<uword fixed_n_elem>
Col<eT>&
Col<eT>::fixed<fixed_n_elem>::operator=(const std::string& text)
  {
  arma_debug_sigprint();
  
  Col<eT>::operator=(text);
  
  return *this; 
  }



template<typename eT>
template<uword fixed_n_elem>
Col<eT>&
Col<eT>::fixed<fixed_n_elem>::operator=(const subview_cube<eT>& X)
  {
  arma_debug_sigprint();
  
  Col<eT>::operator=(X);
  
  return *this; 
  }



template<typename eT>
template<uword fixed_n_elem>
inline
Col<eT>::fixed<fixed_n_elem>::fixed(const std::initializer_list<eT>& list)
  : Col<eT>( arma_fixed_indicator(), fixed_n_elem, ((use_extra) ? mem_local_extra : Mat<eT>::mem_local) )
  {
  arma_debug_sigprint_this(this);
  
  (*this).operator=(list);
  }



template<typename eT>
template<uword fixed_n_elem>
inline
Col<eT>&
Col<eT>::fixed<fixed_n_elem>::operator=(const std::initializer_list<eT>& list)
  {
  arma_debug_sigprint();
  
  const uword N = uword(list.size());
  
  arma_conform_check( (N > fixed_n_elem), "Col::fixed: initialiser list is too long" );
  
  eT* this_mem = (*this).memptr();
  
  arrayops::copy( this_mem, list.begin(), N );
  
  for(uword iq=N; iq < fixed_n_elem; ++iq) { this_mem[iq] = eT(0); }
  
  return *this;
  }



template<typename eT>
template<uword fixed_n_elem>
arma_inline
Col<eT>&
Col<eT>::fixed<fixed_n_elem>::operator=(const fixed<fixed_n_elem>& X)
  {
  arma_debug_sigprint();
  
  if(this != &X)
    {
          eT* dest = (use_extra) ?   mem_local_extra : Mat<eT>::mem_local;
    const eT* src  = (use_extra) ? X.mem_local_extra :        X.mem_local;
    
    arrayops::copy( dest, src, fixed_n_elem );
    }
  
  return *this;
  }



#if defined(ARMA_GOOD_COMPILER)
  
  template<typename eT>
  template<uword fixed_n_elem>
  template<typename T1, typename eop_type>
  inline
  Col<eT>&
  Col<eT>::fixed<fixed_n_elem>::operator=(const eOp<T1, eop_type>& X)
    {
    arma_debug_sigprint();
    
    arma_type_check(( is_same_type< eT, typename T1::elem_type >::no ));
    
    const bool bad_alias = (eOp<T1, eop_type>::proxy_type::has_subview  &&  X.P.is_alias(*this));
    
    if(bad_alias == false)
      {
      arma_conform_assert_same_size(fixed_n_elem, uword(1), X.get_n_rows(), X.get_n_cols(), "Col::fixed::operator=");
      
      eop_type::apply(*this, X);
      }
    else
      {
      arma_debug_print("bad_alias = true");
      
      Col<eT> tmp(X);
      
      (*this) = tmp;
      }
    
    return *this;
    }
  
  
  
  template<typename eT>
  template<uword fixed_n_elem>
  template<typename T1, typename T2, typename eglue_type>
  inline
  Col<eT>&
  Col<eT>::fixed<fixed_n_elem>::operator=(const eGlue<T1, T2, eglue_type>& X)
    {
    arma_debug_sigprint();
    
    arma_type_check(( is_same_type< eT, typename T1::elem_type >::no ));
    arma_type_check(( is_same_type< eT, typename T2::elem_type >::no ));
    
    const bool bad_alias =
      (
      (eGlue<T1, T2, eglue_type>::proxy1_type::has_subview  &&  X.P1.is_alias(*this))
      ||
      (eGlue<T1, T2, eglue_type>::proxy2_type::has_subview  &&  X.P2.is_alias(*this))
      );
    
    if(bad_alias == false)
      {
      arma_conform_assert_same_size(fixed_n_elem, uword(1), X.get_n_rows(), X.get_n_cols(), "Col::fixed::operator=");
      
      eglue_type::apply(*this, X);
      }
    else
      {
      arma_debug_print("bad_alias = true");
      
      Col<eT> tmp(X);
      
      (*this) = tmp;
      }
    
    return *this;
    }
  
#endif



template<typename eT>
template<uword fixed_n_elem>
arma_inline
const Op< typename Col<eT>::template fixed<fixed_n_elem>::Col_fixed_type, op_htrans >
Col<eT>::fixed<fixed_n_elem>::t() const
  {
  return Op< typename Col<eT>::template fixed<fixed_n_elem>::Col_fixed_type, op_htrans >(*this);
  }



template<typename eT>
template<uword fixed_n_elem>
arma_inline
const Op< typename Col<eT>::template fixed<fixed_n_elem>::Col_fixed_type, op_htrans >
Col<eT>::fixed<fixed_n_elem>::ht() const
  {
  return Op< typename Col<eT>::template fixed<fixed_n_elem>::Col_fixed_type, op_htrans >(*this);
  }



template<typename eT>
template<uword fixed_n_elem>
arma_inline
const Op< typename Col<eT>::template fixed<fixed_n_elem>::Col_fixed_type, op_strans >
Col<eT>::fixed<fixed_n_elem>::st() const
  {
  return Op< typename Col<eT>::template fixed<fixed_n_elem>::Col_fixed_type, op_strans >(*this);
  }



template<typename eT>
template<uword fixed_n_elem>
arma_inline
const eT&
Col<eT>::fixed<fixed_n_elem>::at_alt(const uword ii) const
  {
  #if defined(ARMA_HAVE_ALIGNED_ATTRIBUTE)
  
    return (use_extra) ? mem_local_extra[ii] : Mat<eT>::mem_local[ii];
    
  #else
    const eT* mem_aligned = (use_extra) ? mem_local_extra : Mat<eT>::mem_local;
    
    memory::mark_as_aligned(mem_aligned);
    
    return mem_aligned[ii];
  #endif
  }



template<typename eT>
template<uword fixed_n_elem>
arma_inline
eT&
Col<eT>::fixed<fixed_n_elem>::operator[] (const uword ii)
  {
  return (use_extra) ? mem_local_extra[ii] : Mat<eT>::mem_local[ii];
  }



template<typename eT>
template<uword fixed_n_elem>
arma_inline
const eT&
Col<eT>::fixed<fixed_n_elem>::operator[] (const uword ii) const
  {
  return (use_extra) ? mem_local_extra[ii] : Mat<eT>::mem_local[ii];
  }



template<typename eT>
template<uword fixed_n_elem>
arma_inline
eT&
Col<eT>::fixed<fixed_n_elem>::at(const uword ii)
  {
  return (use_extra) ? mem_local_extra[ii] : Mat<eT>::mem_local[ii];
  }



template<typename eT>
template<uword fixed_n_elem>
arma_inline
const eT&
Col<eT>::fixed<fixed_n_elem>::at(const uword ii) const
  {
  return (use_extra) ? mem_local_extra[ii] : Mat<eT>::mem_local[ii];
  }



template<typename eT>
template<uword fixed_n_elem>
arma_inline
eT&
Col<eT>::fixed<fixed_n_elem>::operator() (const uword ii)
  {
  arma_conform_check_bounds( (ii >= fixed_n_elem), "Col::operator(): index out of bounds" );
  
  return (use_extra) ? mem_local_extra[ii] : Mat<eT>::mem_local[ii];
  }



template<typename eT>
template<uword fixed_n_elem>
arma_inline
const eT&
Col<eT>::fixed<fixed_n_elem>::operator() (const uword ii) const
  {
  arma_conform_check_bounds( (ii >= fixed_n_elem), "Col::operator(): index out of bounds" );
  
  return (use_extra) ? mem_local_extra[ii] : Mat<eT>::mem_local[ii];
  }



template<typename eT>
template<uword fixed_n_elem>
arma_inline
eT&
Col<eT>::fixed<fixed_n_elem>::at(const uword in_row, const uword)
  {
  return (use_extra) ? mem_local_extra[in_row] : Mat<eT>::mem_local[in_row];
  }



template<typename eT>
template<uword fixed_n_elem>
arma_inline
const eT&
Col<eT>::fixed<fixed_n_elem>::at(const uword in_row, const uword) const
  {
  return (use_extra) ? mem_local_extra[in_row] : Mat<eT>::mem_local[in_row];
  }



template<typename eT>
template<uword fixed_n_elem>
arma_inline
eT&
Col<eT>::fixed<fixed_n_elem>::operator() (const uword in_row, const uword in_col)
  {
  arma_conform_check_bounds( ((in_row >= fixed_n_elem) || (in_col > 0)), "Col::operator(): index out of bounds" );
  
  return (use_extra) ? mem_local_extra[in_row] : Mat<eT>::mem_local[in_row];
  }



template<typename eT>
template<uword fixed_n_elem>
arma_inline
const eT&
Col<eT>::fixed<fixed_n_elem>::operator() (const uword in_row, const uword in_col) const
  {
  arma_conform_check_bounds( ((in_row >= fixed_n_elem) || (in_col > 0)), "Col::operator(): index out of bounds" );
  
  return (use_extra) ? mem_local_extra[in_row] : Mat<eT>::mem_local[in_row];
  }



template<typename eT>
template<uword fixed_n_elem>
arma_inline
eT*
Col<eT>::fixed<fixed_n_elem>::memptr()
  {
  return (use_extra) ? mem_local_extra : Mat<eT>::mem_local;
  }



template<typename eT>
template<uword fixed_n_elem>
arma_inline
const eT*
Col<eT>::fixed<fixed_n_elem>::memptr() const
  {
  return (use_extra) ? mem_local_extra : Mat<eT>::mem_local;
  }



template<typename eT>
template<uword fixed_n_elem>
inline
const Col<eT>&
Col<eT>::fixed<fixed_n_elem>::fill(const eT val)
  {
  arma_debug_sigprint();
  
  eT* mem_use = (use_extra) ? &(mem_local_extra[0]) : &(Mat<eT>::mem_local[0]);
  
  arrayops::inplace_set_fixed<eT,fixed_n_elem>( mem_use, val );
  
  return *this;
  }



template<typename eT>
template<uword fixed_n_elem>
inline
const Col<eT>&
Col<eT>::fixed<fixed_n_elem>::zeros()
  {
  arma_debug_sigprint();
  
  eT* mem_use = (use_extra) ? &(mem_local_extra[0]) : &(Mat<eT>::mem_local[0]);
  
  arrayops::inplace_set_fixed<eT,fixed_n_elem>( mem_use, eT(0) );
  
  return *this;
  }



template<typename eT>
template<uword fixed_n_elem>
inline
const Col<eT>&
Col<eT>::fixed<fixed_n_elem>::ones()
  {
  arma_debug_sigprint();
  
  eT* mem_use = (use_extra) ? &(mem_local_extra[0]) : &(Mat<eT>::mem_local[0]);
  
  arrayops::inplace_set_fixed<eT,fixed_n_elem>( mem_use, eT(1) );
  
  return *this;
  }



template<typename eT>
inline
Col<eT>::Col(const arma_fixed_indicator&, const uword in_n_elem, const eT* in_mem)
  : Mat<eT>(arma_fixed_indicator(), in_n_elem, 1, 1, in_mem)
  {
  arma_debug_sigprint_this(this);
  }



#if defined(ARMA_EXTRA_COL_MEAT)
  #include ARMA_INCFILE_WRAP(ARMA_EXTRA_COL_MEAT)
#endif



//! @}
