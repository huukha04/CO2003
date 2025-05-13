/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   dataloader.h
 * Author: ltsach
 *
 * Created on September 2, 2024, 4:01 PM
 */

#ifndef DATALOADER_H
#define DATALOADER_H
#include "tensor/xtensor_lib.h"
#include "loader/dataset.h"

using namespace std;

template<typename DType, typename LType>
class DataLoader{
public:
    class Iterator; //forward declaration for class Iterator
    
private:
    Dataset<DType, LType>* ptr_dataset;
    int batch_size;
    bool shuffle;
    bool drop_last;
    int nbatch;
    ulong_tensor item_indices;
    int m_seed;
    xt::svector<Batch<DType, LType>*> batchs;
    
public:
    DataLoader(Dataset<DType, LType>* ptr_dataset, 
            int batch_size, bool shuffle=true, 
            bool drop_last=false, int seed=-1)
                : ptr_dataset(ptr_dataset), 
                batch_size(batch_size), 
                shuffle(shuffle),
                m_seed(seed)
    {
        nbatch = ptr_dataset->len()/batch_size;
        item_indices = xt::arange(0, ptr_dataset->len());
    
        /*TODO: Add your code to do the initialization */
        if (m_seed >= 0 && shuffle) 
        {
            xt::random::seed(m_seed);
        }
        load_constructor();
    
    }
    void load_constructor()
    {
        int len = ptr_dataset->len();
        if (shuffle) xt::random::shuffle(item_indices);

        int ex = len % batch_size;
        nbatch = (len / batch_size);

        auto data_shape = ptr_dataset->get_data_shape();
        data_shape[0] = batch_size;
        xt::xarray<DType> data_batch;

        auto label_shape = ptr_dataset->get_label_shape();
        bool has_label = label_shape.size() > 0;
        xt::xarray<LType> label_batch;  // Move this outside the conditional block

        if (has_label) 
        {
            label_shape[0] = batch_size;
        }

        for (int i = 0; i < nbatch; i++)
        {
            int step = batch_size;
            if (i == nbatch - 1 && !drop_last && ex > 0) 
            {
                step = step + ex;
                data_shape[0] = step;
                if (has_label) label_shape[0] = step;
            }

            data_batch = xt::empty<DType>(data_shape);
            if (has_label) label_batch = xt::empty<LType>(label_shape);


            for (int k = 0; k < step; k++)
            {
                xt::view(data_batch, k) = ptr_dataset->getitem(item_indices[i * batch_size + k]).getData();
                if (has_label) xt::view(label_batch, k) = ptr_dataset->getitem(item_indices[i * batch_size + k]).getLabel();
            }

            if (has_label)
                batchs.push_back(new Batch<DType, LType>(data_batch, label_batch));
            else
                batchs.push_back(new Batch<DType, LType>(data_batch, xt::xarray<LType>{}));
        }
    }
    virtual ~DataLoader()
    { 
        for (auto& batch : batchs)
        {
            delete batch;
        }
    }
    
    //New method: from V2: begin
    int get_batch_size(){ return batch_size; }
    int get_sample_count(){ return ptr_dataset->len(); }
    int get_total_batch(){return int(ptr_dataset->len()/batch_size); }
    
    //New method: from V2: end
    /////////////////////////////////////////////////////////////////////////
    // The section for supporting the iteration and for-each to DataLoader //
    /// START: Section                                                     //
    /////////////////////////////////////////////////////////////////////////
public:

    
    //BEGIN of Iterator

    //YOUR CODE IS HERE: to define iterator
    Iterator                    begin()
    {
        return Iterator(this, 0);
    }
    Iterator                    end()
    {
        return Iterator(this, nbatch);
    }
    class Iterator
    {
    private:
        int cursor;
        DataLoader<DType, LType>* pList;

    public:
        Iterator(DataLoader<DType, LType>* pList = 0, int index = 0)
        {
            this->pList = pList;
            this->cursor = index;
        }
        Batch<DType, LType>& operator*()
        {
            return *pList->batchs[cursor];
        }
        bool        operator!=(const Iterator& iterator)
        {
            return cursor != iterator.cursor;
        }
        // Prefix ++ overload
        Iterator& operator++()
        {
            this->cursor++;
            return *this;
        }
        // Postfix ++ overload
        Iterator    operator++(int)
        {
            Iterator iterator = *this;
            ++*this;
            return iterator;
        }
    };

    //END of Iterator
    
    /////////////////////////////////////////////////////////////////////////
    // The section for supporting the iteration and for-each to DataLoader //
    /// END: Section                                                       //
    /////////////////////////////////////////////////////////////////////////
};


#endif /* DATALOADER_H */

