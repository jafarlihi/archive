import Layout from "src/core/layouts/Layout"
import { BlitzPage } from "@blitzjs/next"
import { APP_NAME } from "src/core/constants"
import { Grid, Spacer } from "@nextui-org/react"
import { useWindowSize, useIntersectionObserver } from "usehooks-ts"
import ThreadCard from "../core/components/ThreadCard"
import CategoryPill from "../core/components/CategoryPill"
import { useEffect, useRef, useState } from "react"
import { invoke, useQuery } from "@blitzjs/rpc"
import getCategories from "src/categories/queries/getCategories"
import { Category, Thread } from "@prisma/client"
import getThreads from "src/threads/queries/getThreads"

const DEFAULT_THREAD_TAKE = 10

const Feed: BlitzPage = (props: any) => {
  const { width } = useWindowSize()
  const [categories] = useQuery(getCategories, undefined)
  const [selectedCategories, setSelectedCategories] = useState<Category[]>([])
  const [threads, setThreads] = useState<Thread[]>([])

  const ref = useRef<HTMLDivElement | null>(null)
  const entry = useIntersectionObserver(ref, {})

  const onFetchThreads = async () => {
    const response = await invoke(getThreads, {
      where: {
        category: {
          id: {
            in: selectedCategories.length ? selectedCategories.map((c) => c.id) : undefined,
          },
        },
      },
      take: DEFAULT_THREAD_TAKE,
      skip: threads.length,
    })
    setThreads((p) => [...p, ...response.threads])
  }

  useEffect(() => {
    if (entry?.isIntersecting) {
      void onFetchThreads()
    }
  }, [entry])

  useEffect(() => {
    setThreads([])
    void onFetchThreads()
  }, [selectedCategories])

  const onCategoryClick = (category: Category) => {
    if (selectedCategories.some((c) => c.id === category.id)) {
      setSelectedCategories((p) => p.filter((c) => c.id !== category.id))
    } else {
      setSelectedCategories((p) => [category, ...p])
    }
  }

  return (
    <Layout title={APP_NAME}>
      <Grid.Container gap={2}>
        <Grid xs={12} sm={1.5}>
          <div
            style={{
              display: "flex",
              flexDirection: width >= 960 ? "column" : "row",
              width: "100%",
            }}
          >
            {categories.categories.map((c: Category) => (
              <CategoryPill
                key={c.id}
                category={c}
                isSelected={selectedCategories.some((sc) => sc.id === c.id)}
                onClick={() => onCategoryClick(c)}
              />
            ))}
          </div>
        </Grid>
        <Grid xs={12} sm={10.5} style={{ flexDirection: "column" }}>
          {threads.map((t) => (
            <>
              <ThreadCard key={t.id} thread={t} />
              <Spacer y={0.5} />
            </>
          ))}
          <div ref={ref} />
        </Grid>
      </Grid.Container>
    </Layout>
  )
}

export default Feed
